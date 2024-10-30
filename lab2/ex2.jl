using JuMP
using HiGHS
import JSON


# extracting data from a json file
model_data = JSON.parse(read("data.json", String))
ex2_data = model_data["ex2"]
products = sort(collect(keys(ex2_data["product_price"])))
machines = sort(collect(keys(ex2_data["machine_cost"])))

# this function states production time
production_time(machine::String, product::String) = ex2_data["production_time"][m][p]

model = Model(HiGHS.Optimizer)

# amounts of products produced
@variable(model, x[products] >= 0, Int)

# constraints
# maximum machine work time
for m in machines
    # dividing by 60 to adjust unit from min to h
    @constraint(model, sum(x[p] * (ex2_data["production_time"][m][p] / 60) for p in products) <=
        ex2_data["max_machine_hours"][m])
end
# number of produced products must be smaller than the maximum demand
for p in products
    @constraint(model, x[p] <= ex2_data["max_demand"][p])
end


# maximizing profit
@objective(model, Max,
    # revenue = liczba produktow * cena
    sum(x[p] * ex2_data["product_price"][p] for p in products)
    # material cost = liczba produktow * materiały
    - sum(x[p] * ex2_data["material_cost"][p] for p in products)
    # machine cost = liczba produktow * czasy wykonywania * koszty
    - sum(
        sum(
            x[p] * (ex2_data["production_time"][m][p] / 60) 
        for p in products) * ex2_data["machine_cost"][m] 
    for m in machines)
)

optimize!(model)

# printing results
println()
println("Profit = ", objective_value(model))
println()
println("Amounts of products made:")
for p in products
    println(p, " => ", value.(x[p]), " kg") 
end
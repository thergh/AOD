using JuMP
using HiGHS
import JSON


# extracting data from a json file
model_data = JSON.parse(read("data.json", String))
ex1_data = model_data["ex1"]
companies = sort(collect(keys(ex1_data["max_fuel"])))
airports = sort(collect(keys(ex1_data["fuel_demand"])))

# this function states cost per gallon
cost_per_gallon(company::String, airport::String) =
    ex1_data["fuel_cost"][company][airport]

model = Model(HiGHS.Optimizer)

# variables
@variable(model, x[companies, airports] >= 0)

# constraints
# companies have limited amount of fuel
@constraint(model, [c in companies], sum(x[c, :]) <= ex1_data["max_fuel"][c])
# airports demand exaact amounts of fueal
@constraint(model, [a in airports], sum(x[:, a]) == ex1_data["fuel_demand"][a])

# minimizing total cost of fuel
@objective(model, Min, sum(cost_per_gallon(c, a) * x[c, a] for c in companies, a in airports))

optimize!(model)
# solution_summary(model)

println()
println("Cost of distribution = ", objective_value(model))
println("Distribution plan:")
for c in companies, a in airports
    println("x[", c, ", ", a, "] = ", value(x[c, a]))
end
println()
println("Distribution by company")
for c in companies
    distri_sum = sum(value(x[c, a]) for a in airports)
    println(c, ": ", distri_sum)
end



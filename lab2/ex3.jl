using JuMP
using HiGHS
import JSON


# extracting data from a json file
model_data = JSON.parse(read("data.json", String))
ex3_data = model_data["ex3"]
periods = sort(collect(keys(ex3_data["production_cost"])))

model = Model(HiGHS.Optimizer)

# variables:
# number of normal products producted in each period
@variable(model, x[periods] >= 0, Int)
# number of additional products producted in each period
@variable(model, y[periods] >= 0, Int)

# the amount of products that were already in the warehouse at the beggining
starting_inventory::Int = ex3_data["starting_inventory"]

# constraints:
# number of products that fit in the warehouse
# start + produced_normal + produced_additional <= demand + capacity
for i = eachindex(periods)  # indexes based on periods
    demand_sum::Int = sum(ex3_data["max_demand"][periods[j]] for j in 1:i)
    produced_normal_sum = sum(x[p] for p in periods[1:i])
    produced_additional_sum = sum(y[p] for p in periods[1:i])
    max_capacity = ex3_data["max_capacity"]
    @constraint(model, produced_normal_sum + produced_additional_sum + starting_inventory <= demand_sum + max_capacity)
end

# all demands must be fulfilled, so produced >= demands for each period
for i = eachindex(periods)
    demand_sum::Int = sum(ex3_data["max_demand"][periods[j]] for j in 1:i)
    produced_normal_sum = sum(x[p] for p in periods[1:i])
    produced_additional_sum = sum(y[p] for p in periods[1:i])
    # demands in all periods must be fulfilled
    @constraint(model, produced_normal_sum + produced_additional_sum + starting_inventory >= demand_sum)
end

# we can only produce less then limits
# production <= production limit + add. production limit
prod_limits = ex3_data["production_limit"]
add_prod_limits = ex3_data["additional_production_limit"]
for p in periods
    # normal production limits must be satisfied:
    @constraint(model, x[p] <= prod_limits[p])
    # additional production limits must be satisfied:
    @constraint(model, y[p] <= add_prod_limits[p])
end


# TESTING PART::

# cost calculation:
normal_cost = sum(x[p] * ex3_data["production_cost"][p] for p in periods)
additional_cost = sum(y[p] * ex3_data["addtional_production_cost"][p] for p in periods)

# initialize storage_cost outside the loop
global storage_cost_sum = 0

# calculating storage cost
for i in eachindex(periods)
    demand_sum::Int = sum(ex3_data["max_demand"][periods[j]] for j in 1:i)
    produced_normal_sum = sum(x[p] for p in periods[1:i])
    produced_additional_sum = sum(y[p] for p in periods[1:i])
    local storage_sum = produced_normal_sum + produced_additional_sum + starting_inventory - demand_sum
    local storage_cost = storage_sum * ex3_data["storage_cost"]
    global storage_cost_sum += storage_cost
    # println(ex3_data["storage_cost"][periods[i]])
end


@objective(model, Min, normal_cost + additional_cost + storage_cost_sum)

optimize!(model)

# printing results
println()
println("cost = ", objective_value(model))

println("period\tnormal\taddit.\tstorage")
for i in eachindex(periods)
    # calculating number of products in the warehouse
    demand_sum::Int = sum(ex3_data["max_demand"][periods[j]] for j in 1:i)
    produced_normal_sum = sum(x[p] for p in periods[1:i])
    produced_additional_sum = sum(y[p] for p in periods[1:i])
    local storage_sum = produced_normal_sum + produced_additional_sum + starting_inventory - demand_sum

    println(periods[i], "\t", value(x[periods[i]]), "\t", value(y[periods[i]]), "\t", value(storage_sum))
end
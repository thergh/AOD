using JuMP
using HiGHS
import JSON


model_data = JSON.parse(read("data.json", String))
ex4_data = model_data["ex4"]
cities = sort(collect(keys(ex4_data["connections"])))
source = ex4_data["source"]
destination = ex4_data["destination"]
max_time = ex4_data["max_time"]

neighbours(city::String) = keys(ex4_data["connections"][city])
time(ci::String, cj::String) = ex4_data["connections"][ci][cj]["time"]
cost(ci::String, cj::String) = ex4_data["connections"][ci][cj]["cost"]

model = Model(HiGHS.Optimizer)


# Bin means that the variable is restricted to binary values
@variable(model, x[cities, cities], Bin)


# cities must be neighbouring to establish a connection
for ci in cities, cj in cities 
    if(!(cj in neighbours(ci)))
        @constraint(model, x[ci, cj] == 0)
    end
end

# duration of the route must be shorter then the maximum
@constraints(model, begin
    sum(x[source, :]) == 1
    sum(x[:, source]) == 0
    sum(x[destination, :]) == 0
    sum(x[:, destination]) == 1
    sum(x[ci, cj] * time(ci, cj) for ci in cities, cj in neighbours(ci)) <= max_time
end)

# in and out degree must be the same if it's not a source / sink
for c in cities
    if(c != source && c != destination)
        @constraint(model, sum(x[c, :]) == sum(x[:, c]))
    end
end

# minimize by the journey cost
@objective(model, Min,
    sum(x[ci, cj] * cost(ci, cj) for ci in cities, cj in neighbours(ci)))


optimize!(model)
solution_summary(model)
         

global city = source
global total_cost = 0
global total_time = 0

println("\nRoute:")
while city != destination
    for neighbour in neighbours(city)
        if value(x[city, neighbour]) == 1
            println(city, " -> ", neighbour)
            global total_cost += cost(city, neighbour)
            global total_time += time(city, neighbour)
            global city = neighbour
        end
    end
end

println("\ntotal cost: ", total_cost)
println("total time: ", total_time)
println("time limit satisfied? ", total_time<= max_time)
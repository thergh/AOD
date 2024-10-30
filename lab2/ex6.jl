using JuMP
using HiGHS
import JSON


# extracting data from a json file
model_data = JSON.parse(read("data.json", String))
ex6_data = model_data["ex6"]
# containers = sort(collect(keys(ex6_data["containers"])))
containers = collect(ex6_data["containers"])
m = ex6_data["board_length"]
n = ex6_data["board_height"]
k = ex6_data["camera_range"]

model = Model(HiGHS.Optimizer)

# variables:
# positions of cameras
@variable(model, x[1:m, 1:n], Bin)

# constraints:

# all containers must be in range of a camera
for c in containers
    pos_m = c[2]["pos_m"]
    pos_n = c[2]["pos_n"]
    # at least one camera in range, ensuring that indices remain in array range
    @constraint(model, sum(x[i, j] for i in max(1, c[2]["pos_m"]-k):min(m, c[2]["pos_m"]+k),
    j in max(1, c[2]["pos_n"]-k):min(n, c[2]["pos_n"]+k)) >= 1)
end

# cameras can't be in the same place as containers
for c in containers
    pos_m = c[2]["pos_m"]
    pos_n = c[2]["pos_n"]
    @constraint(model, x[pos_m, pos_n] == 0)
end

# objective
# minimize number of cameras
@objective(model, Min, sum(x[1:m, 1:n]))

optimize!(model)
solution_summary(model)
         
println("number of cameras: ", objective_value(model))
println()
println("O: camera")
println("X: container")
for i in 1:m
    for j in 1:n
        # checking if there is a container in position m, n
        is_container = any(c[2]["pos_m"] == i && c[2]["pos_n"] == j for c in values(containers))
        
        if value(x[i, j]) == 1
            print("[O]")
        elseif is_container
            print("[X]")
        else
            print("[ ]")
        end
    end
    print("\n")
end


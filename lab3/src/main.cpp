/**
 * TODO:
 * akceptowanie odpowiedniego inputu w mainie
 * czytanie danych z plików podanych w inpucie
 * zwracanie wyników w odpowiednim formacie
 * zapisywanie wyników
 * zrobić strukturę algorytmów w headerze
 */

/**
 * INPUT:
 * - podzielić argumenty na dwójki
 * - jeśli jest parzysta liczba argumentów, error
 * - jeśli pierwszy argument z pary nie zaczyna się '-', error
 * - jeśli ten argument został już wykorzystany, error
 */

#include <iostream>
#include <vector>
#include <utility>
#include <filesystem>
#include <string>

/**
 * Returns 1 if there is an error in the arguments, 0 otherwise
 */
int check_arguments(int argc, char *argv[]){
    if(argc != 8){ /* Wrong number of arguments */
        std::cout << "Error: Wrong number of arguments." << "\n";
        return 1;
    }
    if(std::string(argv[1]) != "dijkstra" && std::string(argv[4]) != "dial" && std::string(argv[1]) != "radixheap"){
        std::cout << "Error: Argument number 1 must be 'dijkstra' or 'dial' or 'radixheap'" << "\n";
        return 1;
    }    
    if(std::string(argv[2]) != "-d"){ /* First argument is always the same */
        std::cout << "Error: Argument number 2 must be '-d'" << "\n";
        return 1;
    }
    if(std::string(argv[4]) != "-ss" && std::string(argv[4]) != "-p2p"){
        std::cout << "Error: Argument number 4 must be '-ss' or '-p2p'" << "\n";
        return 1;
    }
    if(std::string(argv[6]) != "-oss" && std::string(argv[6]) != "-op2p"){
        std::cout << "Error: Argument number 6 must be '-oss' or '-op2p'" << "\n";
        return 1;
    }
    if(std::string(argv[4]) == "-ss" && std::string(argv[6]) != "-oss"){
        std::cout << "Error: Argument number 6 must be '-oss' to match argument 4: '-ss" << "\n";
        return 1;
    }
    if(std::string(argv[4]) == "-p2p" && std::string(argv[6]) != "-op2p"){
        std::cout << "Error: Argument number 6 must be '-op2p' to match argument 4: '-p2p" << "\n";
        return 1;
    }
    if(!(std::filesystem::exists(std::string(argv[3])))){
        std::cout << "Error: File path provided in argument 3 doesn't exist." << "\n";
    }
    if(!(std::string(argv[3]).ends_with(".gr"))){
        std::cout << "Error: File provided in argument 3 has wrong file format. Required format: .gr" << "\n";
    }
    if(std::string(argv[4]) == "-ss" && !(std::string(argv[5]).ends_with(".ss"))){
        std::cout << "Error: File provided in argument 5 has wrong file format. Format must match argument 4: .ss" << "\n";
    }
    if(std::string(argv[4]) == "-p2p" && !(std::string(argv[5]).ends_with(".p2p"))){
        std::cout << "Error: File provided in argument 5 has wrong file format. Format must match argument 4: .p2p" << "\n";
    }




    return 0;
}


enum Algorithm{
    DIJKSTRA,
    DIAL,
    RADIXHEAP
};


enum Mode{
    SS,
    P2P
};


int main(int argc, char *argv[]){
    if(check_arguments(argc, argv)){ /* Something's wrong with arguments */
        return 1;
    }

    /* Setting algorithm */
    Algorithm alg;
    if(std::string(argv[1]) == "dijkstra"){
        alg = DIJKSTRA;
    }
    else if(std::string(argv[1]) == "dial"){
        alg = DIAL;
    }
    else if(std::string(argv[1]) == "radixheap"){
        alg = RADIXHEAP;
    }

    /* Setting mode */
    Mode mode;
    if(std::string(argv[4]) == "-ss"){
        mode = SS;
    }
    else if(std::string(argv[4]) == "-p2p"){
        mode = P2P;
    }






    return 0;
};
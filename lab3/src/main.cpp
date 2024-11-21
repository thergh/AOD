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

    return 0;
}

int main(int argc, char *argv[]){
    if(check_arguments(argc, argv)){ /* Something's wrong with arguments */
        return 1;
    }
    return 0;
};
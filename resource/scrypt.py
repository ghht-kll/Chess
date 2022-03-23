from stockfish import Stockfish
from sys import argv

def write_file(str):
    file = open("lastmove.txt", "w")
    file.write(str)
    file.close()

if __name__ == "__main__":

    stockfish = Stockfish("stockfish") 
    stockfish.set_position(argv[1:])
    result = stockfish.get_best_move_time(500)

    write_file(result)
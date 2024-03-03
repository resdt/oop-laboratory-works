#include <iostream>
#include <memory>

#include "figure.h"
#include "figure_array.h"
#include "rectangle.h"
#include "square.h"
#include "trapezoid.h"

template <Number T>
class MainRoutine {
   private:
    void eraseFigure() {
        size_t n;
        std::cin >> n;
        n--;
        try {
            data.erase(n);
        } catch (std::out_of_range &e) {
            std::cout << e.what() << std::endl;
            return;
        }
        std::cout << "Success.\n";
    }

    void pushFigure() {
        std::string type;
        std::cin >> type;
        try {
            if (type == "square") {
                auto sq = std::make_shared<Square<T>>();
                std::cin >> *sq;
                data.pushBack(sq);
            } else if (type == "rectangle") {
                auto rec = std::make_shared<Rectangle<T>>();
                std::cin >> *rec;
                data.pushBack(rec);
            } else if (type == "trapezoid") {
                auto tr = std::make_shared<Trapezoid<T>>();
                std::cin >> *tr;
                data.pushBack(tr);
            } else {
                std::cout << "Unknown figure name.\n";
                return;
            }
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
            return;
        }
        std::cout << "Success.\n";
    }

    void wholeArea() { std::cout << data.sumOfSquares() << std::endl; }

    void info() {
        std::cout << "Info: \n";
        for (int i = 0; i < data.size(); i++) {
            std::cout << (i + 1) << ":\n";
            std::cout << "  area : " << static_cast<double>(*data[i]) << "\n"
                      << "  сenter : " << data[i]->center() << "\n";
        }
    }

    Array<std::shared_ptr<Figure<T>>> data;

   public:
    void start() {
        std::string command;
        std::cout << "> ";
        while (std::cin >> command) {
            if (command == "push") {
                pushFigure();
            } else if (command == "info") {
                info();
            } else if (command == "erase") {
                eraseFigure();
            } else if (command == "area") {
                wholeArea();
            } else if (command == "exit") {
                break;
            } else {
                std::cout << "Unknown command.\n";
            }
            std::cout << "> ";
        }
    }
};

int main() {
    MainRoutine<double> r;
    r.start();
}
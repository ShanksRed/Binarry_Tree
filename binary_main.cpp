#include <iostream>
#include <iomanip>
#include "binary_tree.h"

void print_tree(binary_tree );
int main() {
	setlocale(LC_ALL, "Russian");
	binary_tree tree;


    int menu{ -1 };

    constexpr std::string_view str_menu[]{
        "0-Выход",
        "1-Просмотреть дерево ",
        "2-Добавить элемент ",
        "3-Рекурсивная вставка элемента",
        "4-Удалить узел",
        "5-Найти элемент",
        "6-Найти элемент(рекурсивно)",
        "7-Найти высоту дерева",
        "8-Удалить дерево",
        "9-Проверка на пустоту",
        "10-Запись в файл",
        "11-Считать из файла"


    };

    auto print_menu = [&]() constexpr {
        for (auto&& element : str_menu) {
            std::cout << element << std::endl;

        }
    };

    auto get_file_path = []() {
        std::string file_path;
        std::cout << "Введите имя файла: ";
        std::cin >> file_path;
        return file_path;
    };

    auto enter_numb = [&](auto number) {
        std::cout << "введите число:";
        std::cin >> number;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            throw std::exception("Ошибка ввода ");
        }
        else {
            return number;
        }
    };

    print_menu();

    while (menu) {
        std::cout << "Введите состояние: "; std::cin >> menu;
        switch (menu)
        {

        case 1:
            print_tree(tree);
            break;
        case 2:
        {
            try {
                int numb{};
                numb = enter_numb(numb);
                tree.insert(numb);

            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        }
        break;
        case 3:
        {
            try {
                int numb{};
                numb = enter_numb(numb);
                tree.insert_recr(numb);
            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        }
        break;
        case 4:
        {
            try {
                int numb{};
                numb = enter_numb(numb);
                tree.delete_node(numb);
            }
            catch (const std::exception& e) {

                std::cout << e.what() << std::endl;
            }
        }
        break;
        case 5:
        {
            try {
                int numb{};
                numb = enter_numb(numb);
                auto answ=tree.find_element(numb);
                if (answ)
                    std::cout << "Элемент есть";
                else
                    std::cout << "Элемента нет";
                std::cout << std::endl;
            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        }
        break;
        case 6:
        {
            try {
                int numb{};
                numb = enter_numb(numb);
                auto answ = tree.find_element_recr(numb);
                if (answ)
                    std::cout << "Элемент есть";
                else
                    std::cout << "Элемента нет";
                std::cout << std::endl;
            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
            }
          
        }
        break;
        case 7:
        {
            auto answ=tree.height();
            std::cout << answ << std::endl;

        }
        break;
        case 8:
        {
            tree.delete_tree();

        }
        break;
        case 9:
        {
            auto answ=tree.is_empty();
            if (answ) std::cout << "Деpево пустое";
            else std::cout << "Деpево не пустое";
            std::cout << std::endl;


        }
        break;
        case 10:
        {
            auto file_path = get_file_path();
            tree.write_to_file(file_path);


        }
        break;
        case 11:
        {
            auto file_path = get_file_path();
            tree.read_fr_file(file_path);


        }
        break;
        case 0:
            break;

        default:
            std::cout << "Ошибка" << std::endl;
        }

    }


	

}

void print_tree(binary_tree tree) {

    if (tree.is_empty())
       std::cout<<"дерево пустое"<<std::endl;
    else {
        auto print_lambd = [](auto&& node) {
            std::cout << node << " ";
        };
        //this->pre_order()
        std::cout << "Прямой обход:" << std::endl;
        std::cout << "    рекурентный: ";
        tree.pre_order_recr(print_lambd);
        std::cout << std::endl;
        std::cout << std::setw(17) << "    обычный: ";
        tree.pre_order(print_lambd);

        std::cout << std::endl;
        std::cout << "Симметричный обход:" << std::endl;
        std::cout << "    рекурентный: ";
        tree.in_order(print_lambd);

        std::cout << std::endl;
        std::cout << "Обратный обход:" << std::endl;
        std::cout << "    рекурентный: ";
        tree.post_order(print_lambd);

        std::cout << std::endl;
        std::cout << "Обход по ширине:" << std::endl;
        std::cout << "               : ";
        tree.bfs_order(print_lambd);
        std::cout << std::endl;
    }

}

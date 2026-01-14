#include <iostream>
#include <cmath>
#include <limits.h>
#include <iomanip>
#include <fstream>

double bring_sqrt(const double x, const double &a) {
    return pow(x,5) + x + a;
}

int get_sign(const double &value){
    if (value >= 0) return 1;
    return 0;
}

struct IterationData{
    size_t idx;
    double answer;
};

IterationData bissection(double left, double right, const double &a, double err = 1e-15){
    std::ofstream out_file_bis("bissection.txt");
    double length = right - left;
    double center = left + length/2;

    if (fabs(bring_sqrt(right, a)) < err) return {0, right};
    if (fabs(bring_sqrt(left, a)) < err) return {0, left};

    std::cout << std::setw(5) << "iter" << std::setw(15) << "left" << std::setw(15) << "center" << std::setw(15)
        << "right" << std::setw(15) << "length" << '\n';

    size_t idx = 0;
    while (length/2 > err){

        out_file_bis << left << ',' << center << ',' << right << ',' << bring_sqrt(center, a) << '\n';
        std::cout << std::setw(5) << idx << std::setw(15) << left << std::setw(15) << center << std::setw(15)
            << right << std::setw(15) << length << '\n';

        if (fabs(bring_sqrt(center, a)) < err) return {idx, center};
        if (get_sign(bring_sqrt(left, a)) != get_sign(bring_sqrt(center, a))){
            right = center;
        } 
        else if(get_sign(bring_sqrt(center, a)) != get_sign(bring_sqrt(right, a))){
            left = center;
        } else{
            return {idx, center};
        }

        length = right - left;
        center = left + length/2;
        idx++;
        if (idx == 100000) break;
    }

    out_file_bis.close();
    return {idx, center};
}

double get_new_x(const double &left, const double &right, const double &a){
    return left - (((right - left) * bring_sqrt(left, a)) / 
                    (bring_sqrt(right, a) - bring_sqrt(left, a)));
}

IterationData chord_method(double left, double right, const double &a, double err = 1e-15){
    
    std::ofstream out_file_chord("chord.txt");
    if (fabs(bring_sqrt(right, a)) <= err) return {0, right};

    std::cout << std::setw(5) << "iter" << std::setw(15) << "left" << std::setw(15) << "right" <<'\n';

    size_t idx = 0;
    double new_x = left;
    while (fabs(right - left) > err){

        out_file_chord << left << ',' << right << ',' << bring_sqrt(new_x, a) << '\n';
        std::cout << std::setw(5) << idx << std::setw(15) << left << std::setw(15) << right <<'\n';

        if (fabs(bring_sqrt(new_x, a)) < err) return {idx, new_x};
        new_x = get_new_x(left, right, a);
        if (get_sign(bring_sqrt(left, a)) != get_sign(bring_sqrt(right, a))){
            left = new_x;
        } else{
            right = new_x;
        }

        idx++;
        if (idx == 1000000) break;
    }

    out_file_chord.close();
    return {idx, new_x};
}

struct StartCoord{
    double left;
    double right;
};

StartCoord get_start_coord(const double &a){
    double left, right;
    if (a >= 0){
        left = -a - 1;
        right = 0;
    } else{
        right = -a + 1;
        left = 0; 
    }

    while (get_sign(bring_sqrt(left, a)) == get_sign(bring_sqrt(right, a))){
        if (a >= 0){
            left *= 2;
        } else{
            right *= 2;
        }
    }
    return StartCoord({left, right});
}

double input(){
    std::cout << "input a: ";
    double a;
    std::cin >> a;
    return a;
}

int main(){
    double a = input();
    double err = 1e-14;
    StartCoord start_coord = get_start_coord(a);
    IterationData answer_bissection = bissection(start_coord.left, start_coord.right, a, err);
    IterationData answer_chord = chord_method(-4.1, -3.8, a, err);
    std::cout << std::setprecision(60) << "Bissection answer: " << answer_bissection.answer << "\nIteration:" << answer_bissection.idx <<'\n';
    std::cout << std::setprecision(60) << "Bring Sqrt: " << bring_sqrt(answer_bissection.answer, a) << '\n';
    std::cout << std::setprecision(60) << "Chord answer: " << answer_chord.answer << "\nIteration:" << answer_chord.idx << '\n';
    std::cout << std::setprecision(60) << "Bring Sqrt: " << bring_sqrt(answer_chord.answer, a) << '\n';
    std::cout << answer_bissection.answer - answer_chord.answer << '\n';

    return 0;
}

//-3.977899393311172815401732805185019969940185546875
//-3.97789939331116837450963430455885827541351318359375
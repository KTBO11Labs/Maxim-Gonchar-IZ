#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
#include<Windows.h>
#include <sstream>
#include <ctime>

using namespace std;

//Функцмя для нахождения клиента в файле об информации о клиентах. return count;
int poc(string name) {
    ifstream file("ClientInfo.txt");
    string check_name;
    int count = 0;
    while (!file.eof()) {
        getline(file, check_name);
        int t = check_name.find_first_of(",");
        check_name.erase(t);
        if (name == check_name) { break; }
        count++;
    }
    file.close();
    return count;
}

//Функция находящая номер клиента. return number;
string get_number(int pozc) {
    ifstream file("ClientInfo.txt");
    string number;
    for (int i = 0; i < pozc+1; i++) { getline(file, number); }
    int t = number.find_first_of(",");
    number.erase(0,t+2);
    t = number.find_first_of(",");
    number.erase(t);
    file.close();
    return number;
}

//Функция находящия колличество услуг у клиента. return count;
int cou(string num) {
    ifstream file("ClientUslug.txt");
    int count = 0;
    string check_num = "";
    while (!file.eof()) {
        getline(file, check_num);
        string c_c_n = check_num;
        int t = c_c_n.find_first_of(",");
        c_c_n.erase(t);
        if (c_c_n == num) {
            count++;
        }
    }
    return count;
    file.close();
}

//функция находящая номер услуги клиента. return check_num;
string get_u(string num,int c) {
    ifstream file("ClientUslug.txt");
    string check_num="";
    while (true) {
        getline(file, check_num);
        string c_c_n = check_num;
        int t = c_c_n.find_first_of(",");
        c_c_n.erase(t);
        if (c_c_n == num) {
            check_num.erase(0, t+2);
            t = check_num.find_first_of(",");
            check_num.erase(t);
            if (c != 0) { c--; }
            else { break; }
        }
    }
    return check_num;
    file.close();
}

//Фуекция узнающая имя учлуги. return name;
string name_u(string num_u) {
    ifstream file("UslugInfo.txt");
    string name = "", code = "", str = "";
    while (!file.eof()) {
        getline(file, str);
        name = str;
        code = str;
        int t = name.find_first_of(",");
        name.erase(t);
        code.erase(0, t+2);
        t = code.find_first_of(",");
        code.erase(t);
        if (code == num_u) {
            return name;
        }
    }
    file.close();
}

//Фуекция узнающая коалифицент учлуги. return k;
string k_u(string num_u) {
    ifstream file("UslugInfo.txt");
    string k = "", code = "", str = "";
    while (!file.eof()) {
        getline(file, str);
        k = str;
        code = str;
        int t = k.find_first_of(",");
        code.erase(0, t + 2);
        k.erase(0, t + 2);
        t = code.find_first_of(",");
        code.erase(t);
        t = k.find_first_of(",");
        k.erase(0, t + 2);
        t = k.find_first_of(",");
        k.erase(t);
        if (code == num_u) {
            return k;
        }
    }
    file.close();
}

//Фуекция узнающая время учлуги. return ti;
string t_u(string num_u) {
    ifstream file("ClientUslug.txt");
    string ti = "", code = "", str = "";
    while (!file.eof()) {
        getline(file, str);
        ti = str;
        code = str;
        int t = code.find_first_of(",");
        code.erase(0, t + 2);
        t = code.find_first_of(",");
        code.erase(t);
        t = ti.find_last_of(",");
        ti.erase(0, t + 2);
        if (code == num_u) {
            return ti;
        }
    }
    file.close();
}

float string_to_float(string s) {
    stringstream ss(s);
    float f;
    if (ss >> f) { return f; }
    else { return 0.0; }
}

float times(string str) {
    if (str == "#") {
        return 1;
    }
    else { float n = string_to_float(str); return n; }
}

int main() {
    system("chcp 1251");
    setlocale(LC_ALL, "russian");
    system("color 0e");
    system("cls");

    cout << "Здравствуете! Эта программа предназначенна для подсчёта стоймости услуг у указаного клиента." << endl;
    cout << "Введите имя фамилию отчёство клиента что васинтересует: ";

    string name, secondname, thirdname;
    //cin >> name >> secondname >> thirdname;
    //name = secondname + " " + name + " " + thirdname;
    getline(cin, name);

    int place_of_client = poc(name);//poc - position of client

    string ci_num = get_number(place_of_client);

    int s = cou(ci_num);
    string* Lu_k = new string[s + 1];//калифицент
    string* Lu_c = new string[s + 1];//код услуги
    string* Lu_n = new string[s + 1];//имя услуги
    string* Lu_t = new string[s + 1];//врямя использованя услуги

    for (int i = 0; i < s; i++) { 
        Lu_c[i] = get_u(ci_num, i);
        Lu_n[i] = name_u(Lu_c[i]);
        Lu_k[i] = k_u(Lu_c[i]);
        Lu_t[i] = t_u(Lu_c[i]);
    }

    cout << name << " ипользовал данные услуги:" << endl << endl << endl;
    for (int i = 0; i < s; i++) {
        float x = times(Lu_k[i]);
        float y = times(Lu_t[i]);
        cout << Lu_n[i] << ", стоимость = " << x*y << "." << endl << endl;
    }
    ofstream rep("Report.txt", ios::trunc);
    time_t currentTime = time(nullptr);
    rep << "Дата и время изменения:" << ctime(&currentTime) << endl;
    rep << name << " ипользовал данные услуги:" << endl << endl << endl;
    for (int i = 0; i < s; i++) {
        float x = times(Lu_k[i]);
        float y = times(Lu_t[i]);
        rep << Lu_n[i] << ", стоимость = " << x * y << endl << endl;
    }
    system("pause");
    return 0;
}
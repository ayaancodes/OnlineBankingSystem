#include <iostream>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

int main() {
    try {
        connection C("dbname=bankapp user=ayaanmunshi hostaddr=127.0.0.1 port=5432");

        if (C.is_open()) {
            cout << "✅ Opened database successfully: " << C.dbname() << endl;
        } else {
            cout << "❌ Can't open database" << endl;
            return 1;
        }

    }
    catch (const std::exception &e) {
        cerr << "❌ Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

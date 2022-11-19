#include<bits/stdc++.h>
#include<fstream>
using namespace std;

// -----------Khởi tạo class cusstomer-----------
class Customer {
private:
    int ID;
    string Name, Email, Phone, Addr, Service, Bill;
public:
    Customer() {};
    void setID(int ID);
    void setName(string Name);
    void setEmail(string Email);
    void setPhone(string Phone);
    void setAddr(string Addr);
    void setService(string Service);
    void setBill(string Bill);
    int getID();
    string getName();
    string getEmail();
    string getPhone();
    string getAddr();
    string getService();
    string getBill();
    void Export_customer_inf();
    void Import_customer_inf();
    Customer(int ID, string Name, string Email, string Phone, string Addr, string Service, string Bill) {
        this->ID = ID;
        this->Name = Name;
        this->Email = Email;
        this->Phone = Phone;
        this->Addr = Addr;
        this->Service = Service;
        this->Bill = Bill;
    }
};

void Customer::setID(int ID) {
    this->ID = ID;
}
void Customer::setName(string Name) {
    this->Name = Name;
}
void Customer::setEmail(string Email) {
    this->Email = Email;
}
void Customer::setPhone(string Phone) {
    this->Phone = Phone;
}
void Customer::setAddr(string Addr) {
    this->Addr = Addr;
}
void Customer::setService(string Service) {
    this->Service = Service;
}
void Customer::setBill(string Bill) {
    this->Bill = Bill;
}

int Customer::getID() {
    return ID;
}
string Customer::getName() {
    return Name;
}
string Customer::getEmail() {
    return Email;
}
string Customer::getPhone() {
    return Phone;
}
string Customer::getAddr() {
    return Addr;
}
string Customer::getService() {
    return Service;
}
string Customer::getBill() {
    return Bill;
}

// -----------Khai báo 1 class node-----------
class NODE {
public:
    Customer data;
    NODE* pNext;
    NODE() {
        this->pNext = NULL;
    }
    NODE(Customer x) {
        this->data = x;
        this->pNext = NULL;
    }
};

// ----------Khai báo 1 class list-------------
class LIST {
public:
    NODE* pHead;
    NODE* pTail;
    LIST() {
        this->pHead = NULL;
        this->pTail = NULL;
    }
    bool IsEmpty() { // Ham check Danh sach co rong hay khong
        if (this->pHead == NULL) return true;
        else return false;
    }
    void ThemCuoi(NODE* p) { // Ham them 1 node vao cuoi danh sach
        if (this->pHead == NULL) { // Neu list rong
            this->pHead = this->pTail = p;
        }
        else {
            this->pTail->pNext = p;
            this->pTail = p;
        }
    }
    // Ham xoa NODE dau tien
    void DeleteFirst() {
        // Neu Danh sach dang rong tra ve list
        if (this->pHead == NULL) {
            return;
        }
        NODE* p = this->pHead;     // Gan 1 node p cho node dau
        this->pHead = this->pHead->pNext; // Gan node dau = node sau
        delete p; // Xoa node p la node dau tien di => node sai chinh la node dau tien
    }
    void DeletaLast() {
        if (this->pHead == NULL) {
            return;
        }
        if (this->pHead->pNext == NULL) {
            DeleteFirst();
            return;
        }
        for (NODE* k = this->pHead; k != NULL; k = k->pNext) {
            if (k->pNext == this->pTail) {
                delete this->pTail;
                k->pNext = NULL;
                this->pTail = k;
            }
        }
    }
    // Ham dem so phan tu node co trong LIST
    int SoPhanTu() {
        int dem = 0;
        for (NODE* k = this->pHead; k != NULL; k = k->pNext) {
            dem++;
        }
        return dem;
    }
    // Ham giai phong bo nho cho LIST
    void ClearList() {
        NODE* k = new NODE();
        while (this->pHead != NULL) {
            k = this->pHead; // Gan node k vao vi tri dau de xoa sau  khi cho pHead tro toi node tiep theo, khong phat sinh loi
            this->pHead = this->pHead->pNext;
            delete k;
        }
    }
    // Ham xuat du lieu trong LIST 
    void Export_DS();

};
// -------------Xử lý FILE--------------------
// hàm đọc dữ liêu 1 dòng từ file
void Read_1_Data_From_File(ifstream& filein, Customer& customer) {
    string s, a[51];
    string Name, Email, Phone, Addr, Service, Bill;
    int ID;
    filein >> ID;
    getline(filein, s);
    int j = 0, count = -1;
    // Lấy độ dài của dòng đang xét đến vị trí cuối
    while (true) {
        if (s[j] == 'V' && s[j + 1] == 'N' && s[j + 2] == 'D') break;
        j++;
    }
    j += 3; // Tăng thêm 3 đơn vị vì đã bị ngắt tại vị trí s[j]=='V;
    for (int i = 0; i < j; i++) {
        if (s[i] == ' ' && s[i + 1] == ' ' && s[i + 2] != ' ') count++;
        if (s[i] == ' ' && s[i + 1] == ' ') {
            continue;
        }
        else {
            a[count] += s[i + 1];
        }
    }
    Name = a[0];
    Email = a[1];
    Phone = a[2];
    Addr = a[3];
    Service = a[4];
    Bill = a[5];
    customer = Customer(ID, Name, Email, Phone, Addr, Service, Bill);
}
//  Lưu dữ liệu từ file vào danh sách liên kết
void Save_Data_From_File_To_LIST(ifstream& filein, LIST& l) {
    // đọc đến cuối file thì dừng
    while (!filein.eof()) {
        Customer customer;
        Read_1_Data_From_File(filein, customer);
        NODE* p = new NODE(customer); // Khởi tạo 1 node person
        l.ThemCuoi(p);
    }
}
// Hàm xuất thông tin customer
void Customer::Export_customer_inf() {
    cout << "\n\tID: " << this->getID();
    cout << "\n\tName: " << this->getName();
    cout << "\n\tEmail: " << this->getEmail();
    cout << "\n\tPhone: " << this->getPhone();
    cout << "\n\tAddress: " << this->getAddr();
    cout << "\n\tService: " << this->getService();
    cout << "\n\tBill: " << this->getBill();

}

// Hàm nhập thông tin Customer
void Customer::Import_customer_inf() {
    int ID;
    string Name, Email, Phone, Addr, Service, Bill;
    cout << "\nNhap ID: ";
    cin >> ID;
    cin.ignore();
    this->setID(ID);
    cout << "\nNhap Ten: ";
    getline(cin, Name);
    this->setName(Name);
    cout << "\nNhap Email: ";
    getline(cin, Email);
    this->setEmail(Email);
    cout << "\nNhap SDT: ";
    getline(cin, Phone);
    this->setPhone(Phone);
    cout << "\nNhap Addr: ";
    getline(cin, Addr);
    this->setAddr(Addr);
    cout << "\nNhap Service: ";
    getline(cin, Service);
    this->setService(Service);
    cout << "\nNhap Bill: ";
    getline(cin, Bill);
    this->setBill(Bill);
}

//xuất danh sách customer
void LIST::Export_DS() {
    int dem = 1;
    for (NODE* k = this->pHead; k != NULL; k = k->pNext) {
        cout << "\n\t\tCusomer thu " << dem++;
        k->data.Export_customer_inf();
        cout << endl;
    }
}

//-------------Thêm thông tin khách hàng------------

// Tìm khoảng cách giữa các tiêu đề
void Find_size_Between_Titles(int& size_ID, int& size_Name, int& size_Email, int& size_Phone, int& size_Address, int& size_Service, int& size_Bill) {
    ifstream filein;
    filein.open("data.txt", ios::in);
    string s;
    getline(filein, s);
    size_ID = 2, size_Name = size_Bill = 4, size_Email = size_Phone = 5, size_Address = size_Service = 7;
    for (int i = 2; i <= s.size(); i++) {
        if (s[i] != ' ') break;
        else size_ID++;
    }
    for (int i = size_ID + size_Name; i <= s.size(); i++) {
        if (s[i] != ' ') break;
        else size_Name++;
    }
    for (int i = size_ID + size_Name + size_Email; i <= s.size(); i++) {
        if (s[i] != ' ') break;
        else size_Email++;
    }
    for (int i = size_ID + size_Name + size_Email + size_Phone; i <= s.size(); i++) {
        if (s[i] != ' ') break;
        else size_Phone++;
    }
    for (int i = size_ID + size_Name + size_Email + size_Phone + size_Address; i <= s.size(); i++) {
        if (s[i] != ' ') break;
        else size_Address++;
    }
    for (int i = size_ID + size_Name + size_Email + size_Phone + size_Address + size_Service; i <= s.size(); i++) {
        if (s[i] != ' ') break;
        else size_Service++;
    }
    for (int i = size_ID + size_Name + size_Email + size_Phone + size_Address + size_Service + size_Bill; i <= s.size(); i++) {
        if (s[i] != ' ') break;
        else size_Bill++;
    }
    filein.close();
}
int  size_ID, size_Name, size_Email, size_Phone, size_Address, size_Service, size_Bill;

// hàm xuất ra các tiêu đề
void Export_Titles(ofstream& fileout) {
    fileout << left << setw(size_ID) << "ID";
    fileout << left << setw(size_Name) << "Name";
    fileout << left << setw(size_Email) << "Email";
    fileout << left << setw(size_Phone) << "Phone";
    fileout << left << setw(size_Address) << "Address";
    fileout << left << setw(size_Service) << "Service";
    fileout << "Bill";
}
// Hàm thêm thông tin 1 customer ra FILE
void Add_Inf_1_Customer(ofstream& fileout, LIST& l) {
    l.pTail->data.setID(l.SoPhanTu());
    fileout << endl << left << setw(size_ID) << l.pTail->data.getID();
    fileout << left << setw(size_Name) << l.pTail->data.getName();
    fileout << left << setw(size_Email) << l.pTail->data.getEmail();
    fileout << left << setw(size_Phone) << l.pTail->data.getPhone();
    fileout << left << setw(size_Address) << l.pTail->data.getAddr();
    fileout << left << setw(size_Service) << l.pTail->data.getService();
    fileout << left << setw(size_Bill) << l.pTail->data.getBill();
}
void Export_Inf_Customer_To_File(ofstream& fileout, LIST& l) {
    Export_Titles(fileout);
    for (NODE* k = l.pHead; k != NULL; k = k->pNext) {
        // k->data.setID(++Dem);
        fileout << endl << left << setw(size_ID) << k->data.getID();
        fileout << left << setw(size_Name) << k->data.getName();
        fileout << left << setw(size_Email) << k->data.getEmail();
        fileout << left << setw(size_Phone) << k->data.getPhone();
        fileout << left << setw(size_Address) << k->data.getAddr();
        fileout << left << setw(size_Service) << k->data.getService();
        fileout << left << setw(size_Bill) << k->data.getBill();
    }
}
// hàm ghi dữ liệu ra FILE
void Write_Data_To_Save_In_File(LIST& l){
    ofstream fileout;
    fileout.open("data.txt", ios::out);
    Export_Inf_Customer_To_File(fileout, l);
    fileout.close();
}
// Hàm đọc dữ liệu từ FILE
void Read_Data_From_File(LIST& l){
    ifstream filein;
    filein.open("data.txt", ios::in);
    string nextLine;
    getline(filein, nextLine);
    Save_Data_From_File_To_LIST(filein, l);
    filein.close();
}
//-------------Xóa thông tin khách hàng---------------

//-------------Sửa thông tin khách hàng---------------
void Modify_ID(LIST& l, LIST& check, string ID) {

};
// void Modify_Name(LIST& l, LIST& check, string Name){
//     for(NODE* k = l.pHead; k != NULL; k = k->pNext){
//         if(strcmp(k->data.getName(), check.pHead->data.getName()) == 0){
//             k->data.setName(Name);
//         }
//     }
// };

void Menu_Find_Customer_Inf(LIST l);
void Edit_Customer_Inf(LIST& l, LIST& check) {
    ofstream fileout;
    int ID_Fix;
    string Name_Fix, Email_Fix, Phone_Fix, Address_Fix, Service_Fix, Bill_Fix;
    int option;

    while (1) {
        system("cls");
        cout << "\t\t|-----------------OPTION------------------|";
        cout << "\n\t\t|     MỜI BẠN NHẬP CÁC LỰA CHỌN SAU     |";
        cout << "\n\t\t|    1. Sửa ID                          |";
        cout << "\n\t\t|    2. Sửa Tên                         |";
        cout << "\n\t\t|    3. Sủa Email                       |";
        cout << "\n\t\t|    4. Sửa Số điện thoại               |";
        cout << "\n\t\t|    5. Sửa địa chỉ                     |";
        cout << "\n\t\t|    6. Sửa dịch vụ                     |";
        cout << "\n\t\t|    7. Sửa Bill                        |";
        cout << "\n\t\t|    0. Quay lại                        |";
        cout << "\n\t\t|-----------------END-------------------|";
        cout << "\n\t\t Moi ban nhap lua chon: ";
        cin >> option;
        cin.ignore();

        switch (option) {
        case 0: {
            l.ClearList();
            cout << "\n\t\tNhan Enter quay lai";
            Menu_Find_Customer_Inf(l);
            break;
        }
        case 2: {
            cout << "\t\tBan muon sua ID thanh: ";
            cin >> ID_Fix;
            break;
        }
              // case 3: {
              //     cout << "\t\tBan muon sua Name thanh: ";
              //     getline(cin, Name_Fix);
              //     Modify_Name(l, check, Name_Fix);
              //     fileout.open("data.txt", ios::out);
              //     Export_Inf_Customer_To_File(fileout, l);
              //     fileout.close();
              //     break;
              // }
        case 4: {
            break;
        }
        case 5: {
            break;
        }
        case 6: {
            break;
        }
        }
    }
}
//-------------Tìm kiếm thông tin khách hàng -------
// Hàm kiểm tra xem xâu nhập vào có bằng xâu trong FILE 
bool Check_Search(string a, string b) {
    //string a: xau con tim kiem
    //string b: xau ban dau trong FILE
    int index = b.find(a);
    if (index < b.size()) return true;
    else return false;
    // bool check = false;
    // for(int i = 0; i < b.size(); i++){
    //     if(a[0] == b[i]){
    //         check = true;
    //         for(int j = 1; j < a.size(); j++){
    //             if(a[j] != b[i+j]){
    //                 check = false;
    //                 break;
    //             }
    //             if(j == a.size()) return check;
    //             else continue;
    //         }
    //     }
    //     else continue;
    // }
    // return check;
    // Dùng hàm FIND
}
// hàm lựa chọn của khách hàng sau khi đã tìm thấy thông tin
void Change_Parameters(LIST& l, LIST& check) {
    int option;
    while (1) {
        system("cls");
        cout << "\t\t|---------------OPTION-----------------|";
        cout << "\n\t\t|     MỜI BẠN NHẬP CÁC LỰA CHỌN        |";
        cout << "\n\t\t|  1. Hiển thị thông tin khách hàng    |";
        cout << "\n\t\t|  2. Sửa thông tin của khách hàng     |";
        cout << "\n\t\t|  0. Quay lai                         |";
        cout << "\n\t\t|----------------END-------------------|";
        cout << "\n\t\tNhập lựa chọn của bạn: ";
        cin >> option;
        switch (option) {
        case 0: {
            l.ClearList();
            cout << "\t\tNhấn Enter để quay lại: ";
            Menu_Find_Customer_Inf(l);
            break;
        }
        case 1: {
            check.Export_DS();
            system("pause");
            break;
        }
        case 2: {
            Edit_Customer_Inf(l, check);
            break;
        }
        }
    }
}
//-------------------------------------------------------
void Find_ID(LIST& l, int ID) {
    LIST check;
    for (NODE* k = l.pHead; k != NULL; k = k->pNext) {
        if (ID == k->data.getID()) {
            NODE* p = new NODE(k->data);
            check.ThemCuoi(p);
        }
    }
    if (check.IsEmpty()) {
        cout << "\t\tKhong tim thay ID phu hop !" << endl;
        system("pause");
        return;
    }
    else {
        cout << "\t\tSo ID tim thay: " << check.SoPhanTu() << endl;
        system("pause");
        Change_Parameters(l, check);
    }
}

void Find_Name(LIST& l, string Name) {
    LIST check;
    for (NODE* k = l.pHead; k != NULL; k = k->pNext) {
        if (Check_Search(Name, k->data.getName())) {
            NODE* p = new NODE(k->data);
            check.ThemCuoi(p);
        }
    }
    if (check.IsEmpty()) {
        cout << "\t\tKhong tim thay Name phu hop !" << endl;
        system("pause");
        return;
    }
    else {
        cout << "\t\tSo Name duoc tim thay: " << check.SoPhanTu() << endl;
        system("pause");
        Change_Parameters(l, check);
    }
}
void Find_Email(LIST& l, string Email) {
    LIST check;
    for (NODE* k = l.pHead; k != NULL; k = k->pNext) {
        if (Check_Search(Email, k->data.getEmail())) {
            NODE* p = new NODE(k->data);
            check.ThemCuoi(p);
        }
    }
    if (check.IsEmpty()) {
        cout << "\t\tKhong tim thay Email phu hop !\n";
        system("pause");
        return;
    }
    else {
        cout << "\t\tSo Email duoc tim thay: " << check.SoPhanTu() << endl;
        system("pause");
        Change_Parameters(l, check);
    }
}

void Find_Phone(LIST l, string Phone) {
    LIST check;
    for (NODE* k = l.pHead; k != NULL; k = k->pNext) {
        if (Check_Search(Phone, k->data.getPhone())) {
            NODE* p = new NODE(k->data);
            check.ThemCuoi(p);
        }
    }
    if (check.IsEmpty()) {
        cout << "\t\tKhong tim thay Phone phu hop !\n";
        system("pause");
        return;
    }
    else {
        cout << "\t\tSo Phone duoc tim thay: " << check.SoPhanTu() << endl;
        system("pause");
        Change_Parameters(l, check);
    }
}

void Find_Address(LIST l, string Address) {
    LIST check;
    for (NODE* k = l.pHead; k != NULL; k = k->pNext) {
        if (Check_Search(Address, k->data.getAddr())) {
            NODE* p = new NODE(k->data);
            check.ThemCuoi(p);
        }
    }
    if (check.IsEmpty()) {
        cout << "\t\tKhong tim thay Address phu hop !\n";
        system("pause");
        return;
    }
    else {
        cout << "\t\tSo Address duoc tim thay: " << check.SoPhanTu() << endl;
        cout << l.SoPhanTu() << endl;
        cout << check.SoPhanTu() << endl;
        system("pause");
        Change_Parameters(l, check);
    }
}

void Find_Service(LIST l, string Service) {
    LIST check;
    for (NODE* k = l.pHead; k != NULL; k = k->pNext) {
        if (Check_Search(Service, k->data.getService())) {
            NODE* p = new NODE(k->data);
            check.ThemCuoi(p);
        }
    }
    if (check.IsEmpty()) {
        cout << "\t\tKhong tim thay Service phu hop !\n";
        system("pause");
        return;
    }
    else {
        cout << "\t\tSo Service duoc tim thay: " << check.SoPhanTu() << endl;
        system("pause");
        Change_Parameters(l, check);
    }
}

void Find_Bill(LIST l, string Bill) {
    LIST check;
    for (NODE* k = l.pHead; k != NULL; k = k->pNext) {
        if (Check_Search(Bill, k->data.getBill())) {
            NODE* p = new NODE(k->data);
            check.ThemCuoi(p);
        }
    }
    if (check.IsEmpty()) {
        cout << "\t\tKhong tim thay Bill phu hop !\n";
        system("pause");
        return;
    }
    else {
        cout << "\t\tSo Bill duoc tim thay: " << check.SoPhanTu() << endl;
        system("pause");
        Change_Parameters(l, check);
    }
}

void MENU(LIST l);
// Menu tim kiem thong tin khach hang
void Menu_Find_Customer_Inf(LIST l) {
    int option;
    int ID;
    string Name, Email, Phone, Address, Service, Bill;
    Read_Data_From_File(l);
    while (1) {
        system("cls");
        cout << "\t\t|-------------------OPTION------------------|";
        cout << "\n\t\t|        Moi ban chon cac lua chon          |";
        cout << "\n\t\t|   1. Tim kiem ID  cua khach hang          |";
        cout << "\n\t\t|   2. Tim kiem Name cua khach hang         |";
        cout << "\n\t\t|   3. Tim kiem Email cua khach hang        |";
        cout << "\n\t\t|   4. Tim kiem Phone cua khach hang        |";
        cout << "\n\t\t|   5. Tim kiem Address cua khach hang      |";
        cout << "\n\t\t|   6. Tim kiem Service cua khach hang      |";
        cout << "\n\t\t|   7. Tim kiem Bill cua khach hang         |";
        cout << "\n\t\t|   0. Quay lai                             |";
        cout << "\n\t\t|--------------------END--------------------|";
        cout << "\n\t\tNhập lựa chọn của bạn: ";
        cin >> option;
        cin.ignore();
        switch (option) {
        case 0: {
            l.ClearList();
            cout << "\n\t\tNhấn Enter để quay lại MENU: ";
            MENU(l);
            break;
        }
        case 1: {
            cout << "\n\t\tMời bạn nhập ID: ";
            cin >> ID;
            Find_ID(l, ID);
            break;
        }
        case 2: {
            cout << "\n\t\tMời bạn nhập Name: ";
            getline(cin, Name);
            Find_Name(l, Name);
            break;
        }
        case 3: {
            cout << "\n\t\tMời bạn nhập Email: ";
            getline(cin, Email);
            Find_Email(l, Email);
            break;
        }
        case 4: {
            cout << "\n\t\tMời bạn nhập Phone: ";
            getline(cin, Phone);
            Find_Phone(l, Phone);
            break;
        }
        case 5: {
            cout << "\n\t\tMời bạn nhập Address: ";
            getline(cin, Address);
            Find_Address(l, Address);
            break;
        }
        case 6: {
            cout << "\n\t\tMoi ban nhap Service: ";
            getline(cin, Service);
            Find_Service(l, Service);\
                break;
        }
        case 7: {
            cout << "\n\t\tMoi ban nhap Bill: ";
            getline(cin, Bill);
            Find_Bill(l, Bill);
        }
        }
    }
}

//-------------Sắp xếp thông tin khách hàng---------
void Swap(Customer& a, Customer& b){
    Customer tmp;
    tmp = a;
    a = b;
    b = tmp;
}
// hàm sắp xếp thông tin khách hàng theo ID từ nhỏ đến lớn
void Sort_ID_Customer_Inf_1(LIST& l) {
    for (NODE* k = l.pHead; k != NULL; k = k->pNext) {
        NODE* minNode = k;
        for (NODE* q = k->pNext; q != NULL; q = q->pNext) {
            if (minNode->data.getID() > q->data.getID()) {
                minNode = q;
            }
        }
        Swap(minNode->data, k->data);
    }
    Write_Data_To_Save_In_File(l);
}
// hàm sắp xếp thông tin khách hàng theo ID từ lớn đến nhỏ
void Sort_ID_Customer_Inf_2(LIST& l) {
    for (NODE* k = l.pHead; k != NULL; k = k->pNext) {
        NODE* minNode = k;
        for (NODE* q = k->pNext; q != NULL; q = q->pNext) {
            if (minNode->data.getID() < q->data.getID()) {
                minNode = q;
            }
        }
        Swap(minNode->data, k->data);
    }
    Write_Data_To_Save_In_File(l);
}

// hàm sắp xếp thông tin khách hàng theo tên Alpahbet
void Sort_Name_Customer_Inf_1(){
    
}
// Hàm sắp xếp thông tin khách hàng theo địa chỉ Alphabet 
void Sort_Address_Customer_Inf();
// Hàm sắp xếp thông tin khách hàng theo Bill, từ lớn đến bé
void Sort_Bill_Customer_Inf();

void MENU_Sort(LIST l) {
    Read_Data_From_File(l);
    int option;
    while (1) {
        system("cls");
        cout << "\t\t|------------------SẮP XẾP---------------------|";
        cout << "\n\t\t|         NHẬP CÁC LỰA CHỌN SAU              |";
        cout << "\n\t\t|      1. Sắp xếp ID từ nhỏ đến lớn          |";
        cout << "\n\t\t|      2. Sắp xếp ID từ lớn đến nhỏ          |";
        cout << "\n\t\t|      3. Sap xep theo dia chi               |";
        cout << "\n\t\t|      4. Sap xep theo Bill                  |";
        cout << "\n\t\t|      0. Quay lại                           |";
        cout << "\n\t\t|------------------END-----------------------|";
        cout << "\n\t\tNhập lựa chọn của bạn: ";

        cin >> option;
        switch (option) {
        case 0: {
            cout << "\n\t\tNhấn Enter để quay lại MENU: ";
            MENU(l);
            break;
        }
        case 1: { 
            Sort_ID_Customer_Inf_1(l);
            cout << "\n\t\tSẮP XẾP THÀNH CÔNG !";
            system("pause");
            break;
        }
        case 2: {
            break;
        }
        case 3: {
            break;
        }
        case 4: {
            break;
        }
        }
    }
}

void MENU(LIST l) {
    int option;
    while (1) {
        system("cls"); // Xoa man hinh de khong hien thi lai Menu nua
        cout << "\t\t|========================MENU==============================|";
        cout << "\n\t\t|                MỜI BẠN NHẬP LỰA CHỌN                     |";
        cout << "\n\t\t| 1. Hiển thị danh sách khách hàng ra khỏi màn hình        |";
        cout << "\n\t\t| 2. Thêm thông tin khách hàng vào FILE                    |";
        cout << "\n\t\t| 3. Xóa thông tin khách hàng cuối cùng trong FILE         |";
        cout << "\n\t\t| 4. Tìm kiếm thông tin khách hàng và chỉnh sửa            |";
        cout << "\n\t\t| 5. Sắp xếp lại thông tin khách hàng                      |";
        cout << "\n\t\t| 0. Thoát Menu                                            |";
        cout << "\n\t\t|========================END===============================|";
        cout << "\n\t\tNhập lựa chọn của bạn: ";
        cin >> option;
        cin.ignore();

        switch (option) {
        case 0: {
            cout << "KẾT THÚC CHƯƠNG TRÌNH !";
            system("pause");
            return;
            break;
        }
        case 1: {
            ifstream filein;
            filein.open("data.txt", ios::in);
            l.ClearList();
            string nextLine;
            getline(filein, nextLine);
            Save_Data_From_File_To_LIST(filein, l);
            if (l.IsEmpty()) {
                cout << "Danh sách rỗng!\n";
                system("pause");
                return;
            }
            else {
                l.Export_DS();
                system("pause");
            }
            filein.close();
            break;
        }
        case 2: {
            l.ClearList();
            Read_Data_From_File(l);

            ofstream fileout;
            fileout.open("data.txt", ios::app);
            Customer x;
            x.Import_customer_inf();
            NODE* p = new NODE(x);
            l.ThemCuoi(p);
            Add_Inf_1_Customer(fileout, l);
            fileout.close();
            break;
        }
        case 3: { //  Ham xoa customer ra khoi FILE
            l.ClearList();
            Read_Data_From_File(l);

            ofstream fileout;
            fileout.open("data.txt", ios::out);
            l.DeletaLast();
            Export_Inf_Customer_To_File(fileout, l);
            fileout.close();
            break;
        }
        case 4: {
            l.ClearList();
            Menu_Find_Customer_Inf(l);
        }
        case 5: {
            l.ClearList();
            MENU_Sort(l);
        }
        }
    }
}
int main() {
    LIST l;
    Customer customer;
    Find_size_Between_Titles(size_ID, size_Name, size_Email, size_Phone, size_Address, size_Service, size_Bill);
    system("Color 0A");
    MENU(l);
}
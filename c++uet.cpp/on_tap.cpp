/**
    Bai 1: Cho mang n so nguyen duong, in ra cac phan tu XUAT HIEN trong mang,
    moi phan tu in DUNG 1 LAN, pt nao xuat hien truoc thi in truoc

    VD: 10
    1 5 3 4 -1 2 -1 -1 6 7
    output: 1 5 3 4 2 6 7

    VD: 12
    2 2 2 2 2 2 2 2 2 2 2 1

    output: 2 1
    int n;
    cin >> n;

    int a[maxn];
    for (int i= 0; i < n; ++i) cin  >> a[i];

    for (int i =0; i < n; ++i)
    {
        if (a[i] > 0) {
            cout << a[i] << ' ';
            for (int j = i+1; j < n; ++j)
            if(a[i] == a[j]) a[j] =-1;
        }
    }


Bai 2: Cho mang n phan tu so nguyen. Kiem tra mang nay la mang "Tang", mang "Giam" hay mang
    "Vo Danh"???

    Tang: a[i] < a[i+1],
    Giam: a[i] > a[i+1],
    Vo Danh: con lai

    5 - 1 2 3 4 5: Tang
    6 - 9 8 5 3 2: Giam
    6 - 9 8 5 3 1 1: VO DANH
    5 - 1 2 3 -2 3: Vo Danh


    if(a[0] < a[1]) t = true;
        else if (a[0] > a[1] g = true;
    else {
        VODANH;
        return 0;
        }

    for (int i = 1; i < n-1; ++i)
    {
        if((t && a[i] >= a[i+1] ||(g && a[i] <= a[i+1]))
        {
            VO DANH;
            return 0;
        }
    }

    if(t) cout << TANG;
        else cout << GIAM;


    mot vong lap for, dung 3 bien t, g, v(int), neu gap a[i] < a[i+1] t++,
     a[i] > a[i+1] g++
    a[i] == a[i+1], v++

    int t(0), g(0);
    for (int i = 0; i < n-1; i++)
    {
        if(a[i]< a[i+1]) t++;
        else if(a[i] > a[i+1] g++;
        else {
            cout << "VO DANH";
            return 0;
        }
    }

    if (t > 0 && g >0) cout << "VO DANH";
    else if (t==0) cout << "GIAM";
    else cout << "TANG";

    HET VONG LAP, bien luan theo t, g, v

    T, G: bool => cung tot.


   Bai 3: Cho 2 mang so nguyen co cung so phan tu,
   Kiem tra xem no co phai la dao nguoc cua nhau khong
    5
    1 2 3 4 5
    6 4 3 2 1

   for (int i = 0;i < n; ++i)
   {
        cin >> a[i];
        cin >> b[i];///SAI QUA
   }

    for (int i = 0;i < n; ++i)
   {
        cin >> b[i];
   }

    for (int i = 0; i < n; ++i)
    {
        if(a[i] != b[n-i -1]) {
            cout << "no";
            return 0;
        }
    }

    cout << "yes";

    int n; cin >> n;
    int a[maxn], b[maxn];
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }

     for (int i = 0; i < n; ++i)
    {
        cin >> b[i];
    }

    output: "yes"

    bool flag (true);
    for (int i = 0; i < n; ++i)
        if(a[i] != b[n-1-i])
        {
            flag = false;
            break;
            }
    if(flag) cout << "yes";
        else cout << "no";

    5
    1 2 3 4 5
    6 4 3 2 1
    output: "no"

    Bai 4: Kiem tra mot mang so nguyen co phai la Mang doi xung khong?
    10
    1 2 3 4 6 5 4 3 2 1

    5
    1 2 3 2 1

    int n;
    cin >> n;
    int a[maxn];
    for (int i =0; i < n; ++i) cin >> a[i];

    bool flag (true);

    for (int i = 0; i < n/2; ++i)
    {
        if(a[i] != a[n-i-1]) {
            flag = false;
            break;
        }
    }

    if(flag) cout << "yes";
        else cout << "no";


Bai 5: Cho mang so nguyen da sap xep va mot so x, KHONG DUNG BAT CU THUAT TOAN SAP XEP NAO
    Chen x vao mang ma mang van giu nguyen thu tu sap xep ban dau

    a[maxn+1]: MANG DU 1 PHAN TU - MANG DAY LA KHONG LAM DUOC

    8
    1 1 3   6 7 8 9 10
    5
    output: 1 1 3 5 6 7 8 9 10

    4
    6 5 2 2
    4
    output: 6 5 4 2 2

    - Xac dinh mang tang hay giam: so sanh a[0] voi a[n-1]
    - Tim vi tri can chen

    int vt = 0;
    while (a[vt] < x && vt < n) vt++;///MANG TANG
    while (a[vt] > x && vt < n) vt++;

    - Dich chuyen tat ca cac phan tu sau vt sang phai 1 vi tri (day tu phan tu cuoi truoc)
    for (int i = n; i > vt; --i)
        a[i] = a[i-1];

   - gan a[vt] = x;






    - Xac dinh mang tang hay giam
    - Tim vi tri can chen
    - Dich cac phan tu phia sau vi tri can chen sang phai 1 vitri
    - Gan a[vt] = x;

    if(a[0] < a[n-1])
    {

    }
    else
    {

    }


Bai Tap ve string:

    1. Dem Tu: "      Con            chau       BAc   Ho": 4 tu, chuyen doi HOA - thuong, thuong - HOA, in nguoc...

    s = " " + s;

    stringstream ss (s);///<sstream>
    string tmp;
    while (ss >> tmp)
    {
        cout << tmp << endl;
        cnt++;
    }



    2. Kiem tra xem mot chuoi co phai mat khau an toan khong: co chu cai thuong, chu cai hoa, co
    chu so va do dai toi thieu la 8

    xet neu do dai len < 8 {NO}
    neu >=8: {///else
        bool lo(false), up(false), di(false);
        for (int i = 0; i < len; ++i)
        {
            if(islower(s[i]) lo = true;
            else if(isupper(s[i]) up = true;
            else if(isdigit(s[i]) di = true;
        }

    if(lo && up && di) YES
        else NO

    3. Cho mot so nguyen DUONG rat lon (100 chu so - string), Tinh tong cac chu so chan cua no, dem cac chu so le....

9999999999999999999999999999999999999999999999999999999999

    4. Dem cac chu so la so nguyen to, số chính phuong,  cua mot so nguyen rat lon (string)
    if(s[i] == '2' || s[i] == '3' || s[i] == '5' || s[i] == '7') cnt++
    if(s == '2')

    s ("");
    char
    s = " "+ s;

    for (int i = 0; i < len; ++i)
    {
        if(s[i] == '2' || s[i] == '3' || s[i] == '5' || s[i] == '7') cnt++;
    }

    5. Tinh tong 2 nguyen rat lon (string)
    VD:
    s1:  0000000000000000000009999999999999999999999999999999999999999999999999
    s2:  1111111111111111111111111111111111111111111118888888888888888888888888
           1111111111111111111121111111111111111111111118888888888888888888888887

    int len1 = s1.length();
    int len2 = s2.length();

    if(len1 < len2)
    {
        while (len1++ < len2) {
            s1 = "0" + s1;
            }
    }
    else
    {
        while (len2++ < len1) {
            s2 = "0" + s2;
            }
    }

    int nho = 0;
    string res("");///LUU "SO" KET QUA

    for (int i = len2 -1; i >=0; --i)
    {
        int tmp = s1[i] - '0' + s2[i] -'0' + nho;///17
        nho = tmp /10; ///==1
        int dv = tmp % 10;///==7
        res = char (dv + '0') + res;
    }

    if(nho) res = "1" + res;

   cout << res;
   999999999999999999999999999999999
   888888888888888888888888888888888
  1888888888888888888888888888888887


    6. Tinh tich cua mot so nguyen rat lon (string) voi mot so nguyen 1 chu so (int)
    VD: 999999999999999999999999999999999999999999999999999999999999999999
           7
     7. Chuan hoa theo ten nguoi:"   nguyen      ai       qUOC   " => "Nguyen Ai Quoc"





    Cong, tru hai so NGUYEN DUONG rat lon (string)
    s1: 000000000000000000000009999999999999999999999999999999999999999999999999999999
    s2: 111111111111111111111111111111111111111111111111111111111111111111111111111111
    1 0
         111111111111111111111112000000000000000000000000000000000000000000000000000000

    99999999999999999999999999999999999999999999999999999999999
    1

    100000000000000000000000000000000000000000000000000000000000
    nhan so nguyen rat lon voi 1 so co 1 chu so

    string s = 99999999999999999999999999999999999999999999999999999999
    int x = 5;

    499999999999999999999999999999999999999999999999999999995

    int nho = 0;
    for (int i = len - 1; i >= 0; --i)
    {
        int tmp = s[i] - 48;
        int t = tmp *x + nho;//45
        nho = t/10;
        res = char (t %10 + 48) + res;
    }

    if (nho) res = char (nho + 48) + res;

        cout << res;

*/







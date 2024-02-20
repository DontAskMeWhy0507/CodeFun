#include <iostream>
#include <string>
struct con_nguoi
{
    con_nguoi(std::string ht,int t,float v1,float cc)
{   ho_ten= ht;
    tuoi = t;
    vong_mot=v1;
    chieu_cao =cc;

}
    std::string  ho_ten;
    int tuoi;
    float vong_mot;
    float chieu_cao;
};

int main (){
    con_nguoi hoi_phu_nu[5] =
    {
    con_nguoi ("thao",22,95,1.65),
    con_nguoi ("lan",18,98,1.70),
    con_nguoi ("huong",29,85,1.6),
    con_nguoi ("nhung",16,98,1.70),
    con_nguoi ("tuyen",30,85,1.6)


    };
   
    con_nguoi *bo_nhi= nullptr ;
    for (int i=0;i<5;i++)
    {
        std::cout<< (hoi_phu_nu[i]).ho_ten<<std::endl;

    }

    return 0;
}
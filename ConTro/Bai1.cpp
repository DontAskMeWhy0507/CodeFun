#include <iostream>
struct con_nguoi
{
    con_nguoi(int t,float v1,float cc)
{   tuoi = t;
    vong_mot=v1;
    chieu_cao =cc;

}
    int tuoi;
    float vong_mot;
    float chieu_cao;
};

int main (){
    con_nguoi thao(22,95,1.65);
   /* thao.tuoi =22;
    thao.vong_mot =95;
    thao.chieu_cao = 1.65; */  
    con_nguoi lan(18,98,1.70);
    con_nguoi huong(29,85,1.6);
    con_nguoi *bo_nhi= nullptr ;
    //Thu 2
    bo_nhi=&thao;           // bồ nhí là địa chỉ còn *bo_nhi là lấy giá trị của địa chỉ đó 
    thao.tuoi =23;
    std::cout<< (*bo_nhi).tuoi <<std::endl;
    //Thu 3
    bo_nhi=bo_nhi+1;
    std::cout<<(*bo_nhi).vong_mot<<std::endl;
    //Thu 4
   /* bo_nhi = nullptr;
    std::cout<<(*bo_nhi).vong_mot<<std::endl; */
    //Thu 5
    bo_nhi = bo_nhi+1;
    std::cout<<(*bo_nhi).chieu_cao<<std::endl;


    return 0;
}
#include <iostream>
#include <string>
#include <random>

using namespace std;

//初期開発終了！！

//引いたカードを数字ではなく何がらの何と表示するようにする

int Point[2]={0,0};
//0はプレイヤー,1は敵
//charは直に代入不可らしい。よってstrcpyを使う
//ポインタをうまく使えないのでstring使います

bool Continue=true;
bool Continue1=true;

string lastC="です";
string dia="ダイヤ";
string spade="スペード";
string clover="クローバー";
string heart="ハート";
string enemy_second="";
string NextPlay="次も遊んでね！";

string DrawCard(int judge){
    random_device rnd;
    mt19937 mt(rnd());
    uniform_int_distribution<> rand52(1,52);
    int a=rand52(mt);
    string b="",c="";
    if(1<=a&&a<14){
        b+=dia;
    }else if(13<a&&a<27){
        b+=spade;
    }else if(26<a&&a<40){
        b+=clover;
    }else{
        b+=heart;
    }
    a=a%13+1;
    if(a==1){
        int Eleven;
        //Aを1とするか11とするかを選択する
        c='A';
        if(judge==0){
            cout <<"1にしますか？それとも11にしますか？選んだ数字を入力してください"<<endl;
            while(Continue1==true){
                cin>>Eleven;
                if(Eleven==1){
                    Point[judge]+=1;
                    Continue1=false;
                }else if(Eleven==11){
                    Point[judge]+=11;
                    Continue1=false;
                }else{
                    cout <<"無効な数字です！１か11を入力してください。"<<endl;
                }
            }
        }else{
            if(Point[1]+11>21){
                Point[1]+=1;
            }else{
                Point[1]+=11;
            }
        }
    }else if(a==11){
        c='J';
        Point[judge]+=10;
    }else if(a==12){
        c='Q';
        Point[judge]+=10;
    }else if(a==13){
        c='K';
        Point[judge]+=10;
    }
    if(c==""){
        c=to_string(a);
        Point[judge]+=a;
        b+="の";
        b+=c;
    }else{
        b+="の";
        b+=c;
    }
    return b;
}

int mycard(){
    string a="あなたの引いたカードは";
    string b=DrawCard(0);
    a+=b;
    a+=lastC;
    cout<<a<<endl;
    return 0;
}
int enemycard(){
    string a="ディーラーの引いたカードは";
    string b=DrawCard(1);
    a+=b;
    a+=lastC;
    cout <<a<<endl;
    return 0;
}

//開始時の表記
int start(){
    cout <<"ゲームを始めます"<<endl;
    mycard();
    mycard();
    enemycard();
    enemy_second=DrawCard(1);
    cout <<"ディーラーの2枚目のカードは秘密です。"<<endl;
    cout <<"あなたの現在の得点は"<<Point[0]<<lastC<<endl;
    return 0;
}

int main(){
    start();
    while(Continue==true){
        string checkContinue;
        cout <<"カードを引きますか？引く場合はYを、引かない場合はNを入力してください。"<< endl;
        cin >>checkContinue;
        if(checkContinue=="Y"){
            mycard();
            cout <<"あなたの現在の得点は"<<Point[0]<<lastC<<endl;
            if(Point[0]>21){
                cout<<"得点が21を超えたため、あなたの負けです。"<<endl;
                cout<<NextPlay<<endl;
                return 0;
            }
        }else if(Point[0]==21){
            cout <<"あなたの現在の得点は"<<Point[0]<<lastC<<endl;
            cout <<"これ以上カード引けないためのあなたのターンを終了します。"<<endl;
            Continue=false;
        }else if(checkContinue=="N"){
            cout <<"あなたのターンを終了します。"<<endl;
            Continue=false;
        }else{
            cout <<"YかNを入力してください！"<<endl;
        }
    }
    //敵のターン
    cout <<"ディーラーの2回目のカードは"<<enemy_second<<lastC<<endl;
    cout <<"ディーラーの現在の得点は"<<Point[1]<<lastC<<endl;
    while(Point[1]<17){
        enemycard();
        cout <<"ディーラーの現在の得点は"<<Point[1]<<lastC<<endl;
    }
    if(Point[1]>21){
        cout <<"あなたの勝ちです！"<<endl<<NextPlay<<endl;
        return 0;
    }else if(Point[0]>Point[1]){
        cout <<"あなたの勝ちです！"<<endl<<NextPlay<<endl;
        return 0;
    }else if(Point[0]==Point[1]){
        cout<<"引き分けです！"<<endl<<NextPlay<<endl;
        return 0;
    }else{
        cout <<"あなたの負けです。"<<endl<<NextPlay<<endl;
        return 0;
    }
    return 0;
}
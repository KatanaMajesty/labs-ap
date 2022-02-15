#include <iostream>
// #include<conio.h> // <- no conio.h on linux. Use curses
#include <curses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iomanip>

using namespace std;

struct teacher //структура викладач
{
    char fio[10]; //прізвище
    char posada[20]; //посада
    float salary; //зарплатня
};
struct stud //структура студента
{
    char fio[10]; //прізвище
    float bal; //середній бал
    float stip; //стипендія
};
struct subject //структура дисципліни
{
    char name[10]; //назва дисципліни
    teacher prepod; //викладач, що читає предмет
    int stnum; //кількість студентів, що вивчають дану дисципліну
    stud student[10] ; //масив студентів, що вивчають предмет
};
int i,j; //лічильники викладачів і студентів
FILE *fp; //покажчик на файл
//------------------------введення даних-------------------------
void input()
{
    subject predmet[10]; //масив дисциплін
    char answer_prep, answer_stud;
    if (fp!=NULL) //якщо файл уже існує
        remove("fp.dat"); //знищення файлу
    else
    {
        fp=fopen("fp.dat","wb");//відкриття файлу для запису
        i=0; //початкове значення лічильника
        do
        {
            cout<<"subject name"<<endl;
            cin>>predmet[i].name;
            cout<<"teacher's surname"<<endl;
            cin>>predmet[i].prepod.fio;
            cout<<"teacher's position"<<endl;
            cin>>predmet[i].prepod.posada;
            cout<<"teacher's salary"<<endl;
            cin>>predmet[i].prepod.salary;
            j=0;
            do
            {
                cout<<"student's surname"<<endl;
                cin>>predmet[i].student[j].fio;
                cout<<"student's ball on subject"<<endl;
                cin>>predmet[i].student[j].bal;
                cout<<"student's scholarship"<<endl;
                cin>>predmet[i].student[j].stip;
                j++;
                cout<<"any students else? y/n"<<endl;
                answer_stud=getch();
            }
            while(answer_stud!='n');
            predmet[i].stnum=j; //кількість студентів по дисципліні
            cout << "contunue input? y/n" << endl;
            answer_prep=getch();
            fwrite(&predmet[i],sizeof(subject),1,fp);//запис предмету до файлу
            i++; //перехід до нового предмету
        }
        while (answer_prep!='n');
        fclose(fp); //закриття файлу
    }
    getch(); //чекати натискання клавіші
}
//-----------------виведення даних по викладачах---------------
void list_prepod()
{
    subject predmet;
    if (!(fp=fopen("fp.dat","rb"))) cerr<<"File do not exist!";
    else
    {
        cout<<"---subject----teacher-----position-----salary \n";
        fread(&predmet,sizeof(subject),1,fp);//читання даних з 1 предмету
        while(!feof(fp)) //доки не кінець файлу
        {
            cout.setf(ios::left); //виведення даних по викладачах
            cout<<" "<<setw(10)<<predmet.name<<setw(12)<<predmet.prepod.fio<<
            setw(14)<<predmet.prepod.posada<<predmet.prepod.salary<<endl;
            fread(&predmet,sizeof(subject),1,fp);//читання даних з 1 предмету
        }
        fclose(fp); //закриття файлу
    }
    getch(); //чекати натискання клавіші
}
//------------------виведення даних по студентах------------------
void list_student()
{
    subject predmet; //дисципліна
    if (!(fp=fopen("fp.dat","rb")))//перевірка існування файлу при відкритті
        cerr<<"File do not exist!";
    else
    {
        cout<<"---teacher----student-----ball---scholarship \n";
        fread(&predmet,sizeof(subject),1,fp); //читання даних з 1 предмету
        while(!feof(fp))
        {
            cout<<" "<<predmet.prepod.fio<<endl;
            for(j=0;j<predmet.stnum;j++) //перегляд студентів по даній
            { // дисципліні
                cout.setf(ios::left); //виведення даних по студентах
                cout<<" "<<
                setw(12)<<predmet.student[j].fio<<setw(10)<<
                predmet.student[j].bal<<predmet.student[j].stip<<endl;
            }
            fread(&predmet,sizeof(subject),1,fp);//читання даних з 1 предмету
        }
        fclose(fp); //закриття файлу
    }
    getch(); //чекати натискання клавіші
}
void read_from_file()
{
    subject predmet;
    if (!(fp=fopen("fp.dat","rb"))) 
        cerr<<"File do not exist!";
    else
    {
        cout<<setw(20)<<"It is file:"<<endl;
        fread(&predmet,sizeof(subject),1,fp); //читання даних з 1 предмету
        while(!feof(fp))
        { //виведення даних з файлу
            cout<<"subject------teacher----position-----salary"<<endl;
            cout.setf(ios::left);
            cout<<setw(12)<<predmet.name<<setw(12)<<predmet.prepod.fio<<
            setw(13)<<predmet.prepod.posada/*<<setw(10)*/<<
            predmet.prepod.salary<<endl;
            cout<<"____Students"<<endl;
            cout<<" fio--------ball-----scholarship"<<endl;
            for(j=0;j<predmet.stnum;j++) //студенти
            {
                cout.setf(ios::left);
                cout<<" "<<setw(12)<<predmet.student[j].fio<<setw(10)<<
                predmet.student[j].bal<<predmet.student[j].stip<<endl;
            }
            fread(&predmet,sizeof(subject),1,fp); //читання даних з 1 предмету
        }
        fclose(fp); //закриття файлу
    }
    getch(); //чекати натискання клавіші
}
//-------------- дисципліна з найвищім середнім балом-------------
void maxbal()
{
    float sr[10]; //середній бал
    subject predmet[15]; //масив предметів
    if (!(fp=fopen("fp.dat","rb"))) 
        cerr<<"File do not exist!";
    else
    {
        i=0;
        fread(&predmet[i],sizeof(subject),1,fp); //читання даних з 1 предмету
        while(!feof(fp))
        {
            sr[i]=0;
            for(j=0;j<predmet[i].stnum;j++) //перегляд студентів
            sr[i]+=predmet[i].student[j].bal;//сума балів студентів по
            //дисципліні
            sr[i]=float(sr[i])/predmet[i].stnum;//середній бал по даному
            //предмету
            i++; //перехід до наступного предмету
            fread(&predmet[i],sizeof(subject),1,fp);//читання даних з 1
            //предмету
        }
        int kol_prep=i; //кількість викладачів
        cout<<" Subject\'s average ball"<<endl;
        for (i=0;i<kol_prep;i++)
        {
            cout.setf(ios::left);
            cout<<setw(10)<<predmet[i].name<<setw(5)<<sr[i]<<endl;
        }
        cout<<"subject with the highest ball: "<<endl;
        float max=sr[0]; //максимальний бал
        int nomer_predmet=0; //номер дисципліни(викладача) у масиві
        //дисциплін
        for(i=1;i<kol_prep;i++) //перегляд дисциплін
        if (max<sr[i])
        {
            max=sr[i]; //визначити максимальний бал й номер дисципліни
            nomer_predmet=i;
        }
        cout<<"max ball="<<max<<" in subject "<<predmet[nomer_predmet].name
        <<" teacher "<<predmet[nomer_predmet].prepod.fio<<endl;
        fclose(fp); //закриття файлу
    }
    getch(); //чекати натискання клавіші
}

//-------------------- перерозподіл стипендій--------------------
void stipendia()
{ 
    float sum=0; //сума стипендій студентів с середнім балом менше 3
    int k=0; //кількість записів про студентів у вхідному масиві
    int l=0; //лічильник всіх студентів
    subject predmet; //предмет
    stud s,tmp[10],stud_tmp[10];//проміжні масиви студентів
    //копіювання даних по студентам у тимчасовий масив
    // без дисциплін та даних по викладачам
    if (!(fp=fopen("fp.dat","rb"))) cerr<<"File do not exist!";
    else
    { 
        fread(&predmet,sizeof(subject),1,fp);
        while(!feof(fp))
        {
            for(j=0;j<predmet.stnum;j++) //перегляд студентів по даній дисципліні
            { //копіювання масиву студентів
                tmp[k]=predmet.student[j];
                k++;
            }
            fread(&predmet,sizeof(subject),1,fp);
        }
        fclose(fp); //закриття файлу
        //середній бал студентів з урахуванням вивчення різних предметів
        int kol[10]; //лічильник предметів, що вивчає один студент
        for (i=0;i<k;i++) //перегляд всього масиву студентів
        {
            stud_tmp[l].bal=0; //сума балів одного студента по різним предметам
            kol[l]=0; //кількість предметів для одного студента
            int f=0; //прапорець обробки даних по студенту
            for (j=0;j<i;j++)//перегляд студентів спочатку масиву до даного запису
            if ((strcmp(tmp[i].fio,tmp[j].fio)==0))
            f=1; //студент вже зустрічався в масиві
            if (f==0) //студент іще не зустрічався в масиві
            {
                for (j=i;j<k;j++) // перегляд масиву від даного запису до кінця
                if (strcmp(tmp[i].fio,tmp[j].fio)==0) //чи є той самий студент
                //по іншому предмету
                {
                    stud_tmp[l].bal+=tmp[j].bal; //накопичення балів
                    //по одному студенту
                    strcpy(stud_tmp[l].fio, tmp[j].fio);//запам'ятати студента
                    stud_tmp[l].stip=tmp[j].stip; //запам'ятати стипендію
                    kol[l]++; //перехід до наступної дисципліни
                }
                //середній бал студента по всім предметам
                stud_tmp[l].bal=float(stud_tmp[l].bal)/kol[l];
                l++; //перехід до наступного студента
            }
        }
        int all_stud=l; //загальна кількість студентів
        //сортування студентів за алфавітом
        for (i=0;i<all_stud;i++)
        for(j=i+1;j<all_stud;j++)
        if (strcmp(stud_tmp[i].fio,stud_tmp[j].fio)>0)
        {
            s=stud_tmp[i];
            stud_tmp[i]=stud_tmp[j];
            stud_tmp[j]=s;
        }
        //виведення даних про загальний середній бал та початкову стипендію
        cout<<"Array of students after sort"<<endl;
        cout<<"--student------average ball------scholarship"<<endl;
        for (i=0;i<all_stud;i++)
        {
            cout.setf(ios::left);
            cout<<setw(20)<<stud_tmp[i].fio<<setw(15)<<stud_tmp[i].bal<<
            stud_tmp[i].stip<<endl;
        }
        getch();
        //обробка студентів з середнім балом менше 3
        j=0; //їх кількість
        for (i=0;i<all_stud;i++)
        if ((stud_tmp[i].bal>=0)&&(stud_tmp[i].bal<3))
        {
            sum+=stud_tmp[i].stip;
            stud_tmp[i].stip=0; //обнулення їх стипендії
            j++;
        }
        for (i=0;i<all_stud;i++) //розподіл між іншими
        if ((stud_tmp[i].bal>=3)&&(stud_tmp[i].bal<=5))
        stud_tmp[i].stip=stud_tmp[i].stip+sum/(all_stud-j);
        //виведення нарахованої стипендії
        cout<<endl<<"Counted scholarship"<<endl;
        cout<<"--FIO------average ball------scholarship"<<endl;
        for(i=0;i<all_stud;i++)
        {
            cout.setf(ios::left);
            cout<<setw(15)<<stud_tmp[i].fio<<setw(15)<<stud_tmp[i].bal;
            if ((stud_tmp[i].bal>=3)&&(stud_tmp[i].bal<=5))
            cout<<stud_tmp[i].stip<<endl;
            else
            cout<<"has no scholarship"<<endl; //стипендія не нарахована
        }
    }
    getch(); //чекати натискання клавіші
}

//---------------------стипендіальний фонд----------------------
void fond()
{
    float fond_prep=0; //фонд викладачів
    float fond_stip=0; //стипендіальний фонд
    subject predmet; //предмет
    stud tmp[10]; //тимчасовий масив студентів
    if (!(fp=fopen("fp.dat","rb"))) cerr<<"File do not exist!";
    else
    {
        fread(&predmet,sizeof(subject),1,fp);
        int k=0;
        while(!feof(fp))
        {
            fond_prep+=predmet.prepod.salary;
            for(j=0;j<predmet.stnum;j++) //перегляд студентів
            //по даній дисципліні
            { //копіювання масиву студентів
                tmp[k]=predmet.student[j];
                k++;
            }
            fread(&predmet,sizeof(subject),1,fp);
        }
        fclose(fp); //закриття файлу
        for (i=0;i<k;i++) //перегляд всього масиву студентів
        {
            int f=0; //прапорець обробки даних по студенту
            for (j=0;j<i;j++)//перегляд студентів спочатку масиву до даного запису
            if ((strcmp(tmp[i].fio,tmp[j].fio)==0))
            f=1; //студент вже зустрічався в масиві
            if (f==0) //студент іще не зустрічався в масиві
            fond_stip+=tmp[i].stip;
        }
        cout<<"salary found ="<<fond_prep<<endl;
        cout<<"scholarship found ="<<fond_stip<<endl;
        if (fond_prep-fond_stip>0)
        cout<<"salary found is bigger "<<endl;
        else
        cout<<"salary found is smaller "<<endl;
    }
    getch(); //чекати натискання клавіші
}

//------------------------головна програма----------------------
void main()
{
    while (1)
    {
        cout<<" MENU \n"<<endl;
        cout<<"1. Database input by keyboard."<<endl;
        cout<<"2. Read data from file."<<endl;
        cout<<"3. View teacher's database."<<endl;;
        cout<<"4. View student's database."<<endl;
        cout<<"5. List of subjects with the highest average ball."<<endl;
        cout<<"6. Scholarship."<<endl;
        cout<<"7. Scholarship found."<<endl;
        cout<<"8. Exit"<<endl;
        cout<<endl;
        int key; //номер пункту меню
        cout<< "Choosen menu item:";
        cin>>key;
        switch(key) // вибір функції реалізації меню
        {
            case 1: {input();break;}
            case 2: {read_from_file();break;}
            case 3: {list_prepod();break;}
            case 4: {list_student();break;}
            case 5: {maxbal();break;}
            case 6: {stipendia();break;}
            case 7: {fond();break;}
            case 8: {exit (0); break;}
            default: {cout<<"Try another time...";getch();break;}
        }
    }
}
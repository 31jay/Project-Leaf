#include<graphics.h>
#include<conio.h>
#include<fstream>
#include<iostream>
#include<dirent.h>
#include<windows.h>
#include<vector>
#include<regex>
#include"generalFunction.h"
#include"AllProjectModules.h"

using namespace std;


// Function to regulate user Login and returns the LoggedIn user at last
string Login()
{
TOP:
    setfillstyle(SOLID_FILL,backgroundColor);
    floodfill(0,0,backgroundColor);
    readimagefile("C:\\User_Data\\asset\\leaflogo.jpg",sWidth(42),sWidth(7), sWidth(58),sWidth(22));           //user icon
    setfillstyle(SOLID_FILL,WHITE);
    settextstyle(0,0,0);
    setfillstyle(SOLID_FILL,textBar);
    setcolor(textBar);
    roundBar(sWidth(28),sHeight(50),sWidth(38),sHeight(53),sWidth(0.5));    //System text to ask LeafHandle
    roundBar(sWidth(28),sHeight(57),sWidth(38),sHeight(60),sWidth(0.5));    //System text to ask password
    setfillstyle(SOLID_FILL,inputBar);
    setcolor(inputBar);
    roundBar(sWidth(40),sHeight(50),sWidth(70),sHeight(53),sWidth(0.5));    //User Input Bar for LeafHandle
    roundBar(sWidth(40),sHeight(57),sWidth(70),sHeight(60),sWidth(0.5));    //User Input Bar for password

    setbkcolor(backgroundColor);
    setcolor(RED);
    settextjustify(CENTER_TEXT,CENTER_TEXT);

    setbkcolor(textBar);
    outtextxy(sWidth(33),sHeight(52),"LeafHandle :");
    outtextxy(sWidth(33),sHeight(59),"Password :");
    setbkcolor(inputBar);
LeafHandle:
    setcolor(BLACK);
    line(sWidth(42),sHeight(53.6),sWidth(68),sHeight(53.6));        //Gives Active Box effect by a black line.
    setcolor(RED);
    string leafHandle=userInput(sWidth(55),sHeight(52));

    if(leafHandle.length()<minHandle||leafHandle.length()>32||leafHandle.find(' ')!=string::npos)         //Checks the character Limit and Space of LeafHandle
    {
        bar(sWidth(40),sHeight(50),sWidth(70),sHeight(53));    //User Input Bar for LeafHandle
        readimagefile("C:\\User_Data\\asset\\warning.jpg",sWidth(68),sHeight(50),sWidth(70),sHeight(53));
        setcolor(RED);
        if(leafHandle.length()<minHandle||leafHandle.length()>32)
            outtextxy(sWidth(55),sHeight(52),"Character Limit (3 - 32)");
        if(leafHandle.find(' ')!=string::npos)
            outtextxy(sWidth(55),sHeight(52),"Contains Space: Invalid Character");
        delay(500);
        ignoreInput();
        getch();
        setcolor(inputBar);
        bar(sWidth(40),sHeight(50),sWidth(70),sHeight(53));    //User Input Bar for LeafHandle
        setcolor(RED);
        goto LeafHandle;
    }
    setcolor(inputBar);
    line(sWidth(42),sHeight(53.6),sWidth(68),sHeight(53.6));        //Gives Active Box effect by a black line.
    setcolor(RED);

    setcolor(BLACK);
    line(sWidth(42),sHeight(60.6),sWidth(68),sHeight(60.6));        //Gives Active Box effect by a black line.
    setcolor(RED);
    string passKey=getpassword(sWidth(55),sHeight(59),false);
    setcolor(inputBar);
    line(sWidth(42),sHeight(60.6),sWidth(68),sHeight(60.6));        //Gives Active Box effect by a black line.
    setcolor(RED);
    ifstream file("C:\\User_Data\\"+leafHandle+"\\profile.txt");
    string uname, key;
    bool found=false;
    if(file.is_open())
    {
        while(file.good())
        {
            file>>uname>>key;

            if(uname==leafHandle && key==passKey)
            {
                found=true;
                break;
            }
            else
                found=false;
        }
    }
    setbkcolor(backgroundColor);
    if(found)
    {
        setcolor(GREEN);
        outtextxy(sWidth(50),sHeight(90),"Authentication Successful !!");
        outtextxy(sWidth(50),sHeight(93),"Logged In !!");
        string userProfile="C:\\User_Data\\"+leafHandle+"\\userprofile.jpg";
        readimagefile(userProfile.c_str(),sWidth(42),sWidth(7), sWidth(58),sWidth(22));           //user icon
        setcolor(RED);
        getch();
        return leafHandle;
    }
    else
    {
        outtextxy(sWidth(50),sHeight(90),"Incorrect Credentials ");
        outtextxy(sWidth(50),sHeight(93),"FORGOT PASSWORD ? [1]");
        char choice=getch();
        cleardevice();
        if(choice=='1')
        {
            settextstyle(0,0,0);
            setfillstyle(SOLID_FILL,textBar);
            setcolor(textBar);
            setbkcolor(textBar);
            roundBar(sWidth(28),sHeight(44),sWidth(38),sHeight(47),sWidth(0.5));    //System text to ask Age
            roundBar(sWidth(28),sHeight(51),sWidth(38),sHeight(54),sWidth(0.5));    //System text to ask Password
            roundBar(sWidth(28),sHeight(58),sWidth(38),sHeight(61),sWidth(0.5));    //System text to ask Password Confirmation
            roundBar(sWidth(28),sHeight(65),sWidth(38),sHeight(68),sWidth(0.5));    //System text to ask Password Confirmation

            setfillstyle(SOLID_FILL,inputBar);
            setcolor(inputBar);
            roundBar(sWidth(40),sHeight(44),sWidth(70),sHeight(47),sWidth(0.5));    //User Input to ask Old Password
            roundBar(sWidth(40),sHeight(51),sWidth(70),sHeight(54),sWidth(0.5));    //User INput to ask Password
            roundBar(sWidth(40),sHeight(58),sWidth(70),sHeight(61),sWidth(0.5));    //User Input to ask Password Confirmation
            roundBar(sWidth(40),sHeight(65),sWidth(70),sHeight(68),sWidth(0.5));    //User Input to ask Password Confirmation

            settextjustify(CENTER_TEXT,CENTER_TEXT);
            setbkcolor(textBar);
            setcolor(RED);
            outtextxy(sWidth(33),sHeight(46),"LeafHandle :");
            outtextxy(sWidth(33),sHeight(53),"Reset PIN :");
            outtextxy(sWidth(33),sHeight(60),"New Password :");
            outtextxy(sWidth(33),sHeight(67),"Confirmation :");

            string handle,pin, newPassword, confirmedNew;

            setfillstyle(SOLID_FILL,inputBar);
            setbkcolor(inputBar);
            setcolor(BLACK);
            line(sWidth(42),sHeight(47.6),sWidth(68),sHeight(47.6));        //Gives Active Box effect by a black line.
            setcolor(RED);
            handle=userInput(sWidth(55),sHeight(46));
            setcolor(inputBar);
            line(sWidth(42),sHeight(47.6),sWidth(68),sHeight(47.6));        //Removes Active Box effect by a black line.
            setcolor(RED);
            string path="C:\\User_Data\\"+handle;
            DIR* dir=opendir(path.c_str());
            if(!dir)
            {
                readimagefile("C:\\User_Data\\asset\\warning.jpg",sWidth(68),sHeight(44),sWidth(70),sHeight(47));
                outtextxy(sWidth(55),sHeight(46),"User doesnot exist");
                getch();
                delay(200);
                ignoreInput();
                cleardevice();
                return "";
            }
            else
            {
                readimagefile("C:\\User_Data\\asset\\verified.jpg",sWidth(68),sHeight(44),sWidth(70),sHeight(47));
            }

            string fileName="C:\\User_Data\\"+handle+"\\profile.txt";
            string fileUser, filePassword, filePIN;

            ifstream file(fileName);
            file>>fileUser>>filePassword>>filePIN;
            file.close();

            setcolor(BLACK);
            line(sWidth(42),sHeight(54.6),sWidth(68),sHeight(54.6));        //Gives Active Box effect by a black line.
            setcolor(RED);
            pin=resetCode(sWidth(55),sHeight(53));
            setcolor(inputBar);
            line(sWidth(42),sHeight(54.6),sWidth(68),sHeight(54.6));        //Gives Active Box effect by a black line.
            setcolor(RED);
            if(pin==filePIN)
            {
                readimagefile("C:\\User_Data\\asset\\verified.jpg",sWidth(68),sHeight(51),sWidth(70),sHeight(54));
            }
            else
            {
                readimagefile("C:\\User_Data\\asset\\warning.jpg",sWidth(68),sHeight(51),sWidth(70),sHeight(54));
                outtextxy(sWidth(55),sHeight(53),"PIN doesnot match");
                getch();
                delay(200);
                ignoreInput();
                cleardevice();
                return "";
            }

            setcolor(BLACK);
            line(sWidth(42),sHeight(61.6),sWidth(68),sHeight(61.6));        //Gives Active Box effect by a black line.
            setcolor(RED);
            newPassword=getpassword(sWidth(55),sHeight(60),true);
            setcolor(inputBar);
            line(sWidth(42),sHeight(61.6),sWidth(68),sHeight(61.6));        //Gives Active Box effect by a black line.
            setcolor(RED);
            if(newPassword==filePassword)
            {
                readimagefile("C:\\User_Data\\asset\\warning.jpg",sWidth(68),sHeight(58),sWidth(70),sHeight(61));
                outtextxy(sWidth(55),sHeight(60),"Same as old password !");
                getch();
                delay(200);
                ignoreInput();
                cleardevice();
                return "";
            }
            else
            {
                readimagefile("C:\\User_Data\\asset\\verified.jpg",sWidth(68),sHeight(58),sWidth(70),sHeight(61));
            }

            setcolor(BLACK);
            line(sWidth(42),sHeight(68.6),sWidth(68),sHeight(68.6));        //Gives Active Box effect by a black line.
            setcolor(RED);
            confirmedNew=getpassword(sWidth(55),sHeight(67),false);
            setcolor(inputBar);
            line(sWidth(42),sHeight(68.6),sWidth(68),sHeight(68.6));        //Gives Active Box effect by a black line.
            setcolor(RED);
            if(newPassword!=confirmedNew)
            {
                readimagefile("C:\\User_Data\\asset\\warning.jpg",sWidth(68),sHeight(65),sWidth(70),sHeight(68));
                outtextxy(sWidth(55),sHeight(60),"Not Matched !");
                getch();
                delay(200);
                ignoreInput();
                cleardevice();
                return "";
            }
            else
            {
                readimagefile("C:\\User_Data\\asset\\verified.jpg",sWidth(68),sHeight(65),sWidth(70),sHeight(68));
            }

            editString(fileName,filePassword,newPassword);
            setcolor(GREEN);
            outtextxy(sWidth(50),sHeight(85),"PassWord Changed SuccessFully. ");
            getch();
            setcolor(RED);
            cleardevice();
            return "";
        }
        else
            return "";
    }
}

void signUp()
{
    setfillstyle(SOLID_FILL,backgroundColor);
    floodfill(0,0,backgroundColor);
    readimagefile("C:\\User_Data\\asset\\leafbanner.jpg",sWidth(20),sHeight(0),sWidth(80),sHeight(20));        //Displays Leaf Banner at top
    settextstyle(0,0,0);
    setfillstyle(SOLID_FILL,textBar);
    setcolor(textBar);
    roundBar(sWidth(28),sHeight(30),sWidth(38),sHeight(33),sWidth(0.5));    //System text to ask Full Name
    roundBar(sWidth(28),sHeight(37),sWidth(38),sHeight(40),sWidth(0.5));    //System text to ask Nickname
    roundBar(sWidth(28),sHeight(44),sWidth(38),sHeight(47),sWidth(0.5));    //System text to ask Age
    roundBar(sWidth(28),sHeight(51),sWidth(38),sHeight(54),sWidth(0.5));    //System text to ask Password
    roundBar(sWidth(28),sHeight(58),sWidth(38),sHeight(61),sWidth(0.5));    //System text to ask Password Confirmation
    roundBar(sWidth(28),sHeight(65),sWidth(38),sHeight(68),sWidth(0.5));    //System text to ask Password Reset Code
    setfillstyle(SOLID_FILL,inputBar);
    setcolor(inputBar);
    roundBar(sWidth(40),sHeight(30),sWidth(70),sHeight(33),sWidth(0.5));    //User Input Full Name
    roundBar(sWidth(40),sHeight(37),sWidth(70),sHeight(40),sWidth(0.5));    //User Input to ask Nickname
    roundBar(sWidth(40),sHeight(44),sWidth(70),sHeight(47),sWidth(0.5));    //User Input to ask Age
    roundBar(sWidth(40),sHeight(51),sWidth(70),sHeight(54),sWidth(0.5));    //User INput to ask Password
    roundBar(sWidth(40),sHeight(58),sWidth(70),sHeight(61),sWidth(0.5));    //User Input to ask Password Confirmation
    roundBar(sWidth(40),sHeight(65),sWidth(70),sHeight(68),sWidth(0.5));    //User Input to ask Password Reset Code

    setbkcolor(backgroundColor);
    setcolor(RED);
    settextjustify(CENTER_TEXT,CENTER_TEXT);

    setbkcolor(textBar);
    outtextxy(sWidth(33),sHeight(32),"Full Name :");
    outtextxy(sWidth(33),sHeight(39),"LeafHandle :");
    outtextxy(sWidth(33),sHeight(46),"Password :");
    outtextxy(sWidth(33),sHeight(53),"Confirmation :");
    outtextxy(sWidth(33),sHeight(60),"Profile Image :");
    outtextxy(sWidth(33),sHeight(67),"Reset Code :");

    //Get Full Name ..................
    setbkcolor(inputBar);
    setcolor(BLACK);
    line(sWidth(42),sHeight(33.6),sWidth(68),sHeight(33.6));        //Gives Active Box effect by a black line.
    setcolor(RED);
    string fullName=userInput(sWidth(55),sHeight(32));
    setcolor(inputBar);
    line(sWidth(42),sHeight(33.6),sWidth(68),sHeight(33.6));        //Removes Active Box effect by a black line.

//Get LeafHandle......................
LeafHandle:
    setcolor(BLACK);
    line(sWidth(42),sHeight(40.6),sWidth(68),sHeight(40.6));        //Gives Active Box effect by a black line.
    setcolor(RED);
    string leafHandle=userInput(sWidth(55),sHeight(39));
    DIR *dir = opendir(("C:\\User_Data\\" + leafHandle).c_str());
    if(leafHandle.length()<minHandle||leafHandle.length()>32||leafHandle.find(' ')!=string::npos||dir)         //Checks the character Limit and Space of LeafHandle
    {
        bar(sWidth(40),sHeight(37),sWidth(70),sHeight(40));    //User Input Bar for LeafHandle
        readimagefile("C:\\User_Data\\asset\\warning.jpg",sWidth(68),sHeight(37),sWidth(70),sHeight(40));
        setcolor(RED);
        if(leafHandle.length()<minHandle||leafHandle.length()>32)
            outtextxy(sWidth(55),sHeight(39),"Character Limit (3 - 32)");
        if(leafHandle.find(' ')!=string::npos)
            outtextxy(sWidth(55),sHeight(39),"Contains Space: Invalid Character");
        if(dir)
            outtextxy(sWidth(55),sHeight(39),"LeafHandle Already Taken !!");
        closedir(dir);
        delay(500);
        ignoreInput();
        getch();
        setcolor(inputBar);
        bar(sWidth(40),sHeight(37),sWidth(70),sHeight(40));    //User Input Bar for LeafHandle
        setcolor(RED);
        goto LeafHandle;
    }
    else
        readimagefile("C:\\User_Data\\asset\\verified.jpg",sWidth(68),sHeight(37),sWidth(70),sHeight(40));

    setcolor(inputBar);
    line(sWidth(42),sHeight(40.6),sWidth(68),sHeight(40.6));        //Removes Active Box effect by a black line.
    setcolor(RED);
    //*****************************************
    //Get Password...................

Password:
    setcolor(BLACK);
    line(sWidth(42),sHeight(47.6),sWidth(68),sHeight(47.6));        //Gives Active Box effect by a black line.
    setcolor(RED);
    string password=getpassword(sWidth(55),sHeight(46),true);
    setcolor(inputBar);
    line(sWidth(42),sHeight(47.6),sWidth(68),sHeight(47.6));        //Removes Active Box effect by a black line.
    setcolor(RED);

    setcolor(BLACK);
    line(sWidth(42),sHeight(54.6),sWidth(68),sHeight(54.6));        //Gives Active Box effect by a black line.
    setcolor(RED);
    string verifyPassword=getpassword(sWidth(55),sHeight(53),false);

    setcolor(inputBar);
    line(sWidth(42),sHeight(54.6),sWidth(68),sHeight(54.6));        //Removes Active Box effect by a black line.
    setcolor(RED);

    if(verifyPassword==password)
    {
        readimagefile("C:\\User_Data\\asset\\verified.jpg",sWidth(68),sHeight(51),sWidth(70),sHeight(54));
    }
    else
    {
        readimagefile("C:\\User_Data\\asset\\warning.jpg",sWidth(68),sHeight(51),sWidth(70),sHeight(54));
        outtextxy(sWidth(55),sHeight(53),"Password Not Matched");
        getch();
        delay(200);
        ignoreInput();
        setfillstyle(SOLID_FILL,inputBar);
        bar(sWidth(40),sHeight(44),sWidth(70),sHeight(47.5));
        bar(sWidth(40),sHeight(51),sWidth(70),sHeight(54.5));
        goto Password;
    }


    //Select Profile Image
    setcolor(BLACK);
    line(sWidth(42),sHeight(61.6),sWidth(68),sHeight(61.6));        //Gives Active Box effect by a black line.
    setcolor(RED);
    string profileImage;
    outtextxy(sWidth(55),sHeight(60),"Press Enter to Skip; Any key to Select");
    char choice=getch();
    delay(300);
    ignoreInput();
    outtextxy(sWidth(55),sHeight(60),"                                         ");
    if(choice==13)
    {
        outtextxy(sWidth(55),sHeight(60),"No Image Selected");
    }
    else
    {
        profileImage=profileLocation();
        if(profileImage.empty())
            outtextxy(sWidth(55),sHeight(60),"No Image Selected");
        else
        {
            readimagefile(profileImage.c_str(),sWidth(68),sHeight(58),sWidth(70),sHeight(61));
            if(profileImage.length()>30)
                outtextxy(sWidth(55),sHeight(60),const_cast<char*>((profileImage.substr(profileImage.length() - 30)).c_str()));
            else
                outtextxy(sWidth(55),sHeight(60),const_cast<char*>(profileImage.c_str()));
        }
    }
    setcolor(inputBar);
    line(sWidth(42),sHeight(61.6),sWidth(68),sHeight(61.6));        //Removes Active Box effect by a black line.
    setcolor(RED);

    //RESET CODE
    //*********************************
    setcolor(BLACK);
    line(sWidth(42),sHeight(68.6),sWidth(68),sHeight(68.6));        //Gives Active Box effect by a black line.
    setcolor(RED);
    string resetStr=resetCode(sWidth(55),sHeight(67));
    string displayStr="Use this code to Change Password: "+resetStr;
    outtextxy(sWidth(55),sHeight(67),const_cast<char*>(displayStr.c_str()));
    getch();
    setcolor(inputBar);
    line(sWidth(42),sHeight(68.6),sWidth(68),sHeight(68.6));        //Removes Active Box effect by a black line.
    setcolor(RED);


    //Creates a directory ( Folder) for new User:
    string newFolder="C:\\User_Data\\"+leafHandle;
    mkdir(newFolder.c_str());

    // Stores User Details to a file:
    ofstream userFile(newFolder+"\\profile.txt");
    userFile<<leafHandle<<" "<<verifyPassword<<" "<<resetStr<<" "<<fullName<<endl;
//    userFile<<"Full Name: "<<fullName<<endl;
//    userFile<<"Handle: "<<leafHandle<<endl;
//    userFile<<"Password: "<<verifyPassword<<endl;
//    userFile<<"Reset Code: "<<resetStr<<endl;
    string finalImage=newFolder+"\\userprofile.jpg";
    if(!profileImage.empty())
        copyImage(profileImage,finalImage);

    string dir1="C:\\User_Data\\"+leafHandle+"\\Genre";
    string dir2="C:\\User_Data\\"+leafHandle+"\\Tags";
    string dir3="C:\\User_Data\\"+leafHandle+"\\Shared";
    string dir4="C:\\User_Data\\"+leafHandle+"\\Lits";
    string dir5="C:\\User_Data\\"+leafHandle+"\\Notes";
    string dir6="C:\\User_Data\\"+leafHandle+"\\Templates";

    mkdir(dir1.c_str());
    mkdir(dir2.c_str());
    mkdir(dir3.c_str());
    mkdir(dir4.c_str());
    mkdir(dir5.c_str());
    mkdir(dir6.c_str());
    setcolor(GREEN);
    outtextxy(sWidth(50),sHeight(80),"Account Created SuccessFully. ");
    outtextxy(sWidth(50),sHeight(83),"Continue to Login !!");
    setcolor(RED);
    getch();
}


string loginSignUp()
{
UserLogin:
    setfillstyle(SOLID_FILL,backgroundColor);
    floodfill(0,0,backgroundColor);
    readimagefile("C:\\User_Data\\asset\\leafLogo.jpg",sWidth(35),sHeight(40),sWidth(50),sHeight(60));
    readimagefile("C:\\User_Data\\asset\\SignIn.jpg",sWidth(50),sHeight(40),sWidth(60),sHeight(50));
    readimagefile("C:\\User_Data\\asset\\one.jpg",sWidth(61),sHeight(42.5),sWidth(64),sHeight(47.5));

    readimagefile("C:\\User_Data\\asset\\SignUp.jpg",sWidth(50),sHeight(50),sWidth(60),sHeight(60));
    readimagefile("C:\\User_Data\\asset\\two.jpg",sWidth(61),sHeight(52.5),sWidth(64),sHeight(57.5));

    readimagefile("C:\\User_Data\\asset\\help.jpg",sWidth(50),sHeight(90),sWidth(60),sHeight(98));
    readimagefile("C:\\User_Data\\asset\\three.jpg",sWidth(61),sHeight(92),sWidth(64),sHeight(96));
    string loggedInUser;
    char choice=getch();                //TO get the user Choice for login/Signup...
    if(choice=='1')                     // Choice 1: login() func is called which returns the loggedIn user if logIn is successful and returns blank if unsuccessful.
    {
        cleardevice();
        loggedInUser=Login();
        if(loggedInUser.empty())
            goto UserLogin;
        else
            return loggedInUser;
    }
    else if(choice=='2')                // User SignUp Func is called and registers the user.
    {
        cleardevice();
        signUp();
        cleardevice();
        goto UserLogin;
    }
    else if(choice=='3')
    {
        cleardevice();                  //Some help texts are diaplayed...
        setfillstyle(SOLID_FILL,backgroundColor);
        floodfill(0,0,backgroundColor);
        string helpTxt;
        int textHeight=0;
        setbkcolor(backgroundColor);
        ifstream file("C:\\User_Data\\asset\\help.txt");
        while (file.good())
        {
            getline(file, helpTxt);
            settextjustify(LEFT_TEXT,CENTER_TEXT);
            setcolor(BLACK);
            print_Lines(sWidth(40),sHeight(35)+textHeight,helpTxt);
            textHeight+=textheight(const_cast<char*>(helpTxt.c_str()));
            delay(50);
            ignoreInput();
        }
        setcolor(RED);
        settextjustify(CENTER_TEXT,CENTER_TEXT);
        getch();
        cleardevice();
        goto UserLogin;
    }
    else
    {
        delay(200);                 //If other than defined keys are pressed does nothing and gets ready for next input.
        ignoreInput();
        goto UserLogin;
    }
}

//**************************************
//Home page Module.....
//****************************************

void homePage(string user_loggedIN)
{
    string user_upperCase=user_loggedIN;
    for (char &c : user_upperCase)
    {
        c = toupper(c);
    }
    setbkcolor(backgroundColor);
    setfillstyle(SOLID_FILL,backgroundColor);
    floodfill(0,0,backgroundColor);

    setcolor(RED);
    setfillstyle(SOLID_FILL,GREEN);
    bar(sWidth(1),sWidth(9),sWidth(99),sWidth(9.5));
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(8,0,3);
    outtextxy(sWidth(83),sWidth(4),"Welcome, ");
    settextjustify(RIGHT_TEXT,CENTER_TEXT);
    outtextxy(sWidth(88),sWidth(6),(const_cast<char*>(user_upperCase.c_str())));
    string imageFile="C:\\User_Data\\"+user_loggedIN+"\\userprofile.jpg";
    readimagefile(const_cast<char*>(imageFile.c_str()),sWidth(90),sWidth(1),sWidth(99),sWidth(9));

    readimagefile("C:\\User_Data\\asset\\create.jpg",sWidth(15),sHeight(40),sWidth(25),sHeight(55));
    readimagefile("C:\\User_Data\\asset\\read.jpg",sWidth(30),sHeight(40),sWidth(40),sHeight(55));

    string checkFile="C:\\User_Data\\"+user_loggedIN+"\\messages.txt";
    int msgCount=0;
    ifstream file(checkFile);
    if(file.is_open())
    {
        while(file.good())
        {
            string lineFile;
            getline(file,lineFile);
            msgCount++;
        }
    }
    file.close();
    string totalMsg=to_string(msgCount-1);
    if(msgCount==0)
        readimagefile("C:\\User_Data\\asset\\myAccount.jpg",sWidth(45),sHeight(40),sWidth(55),sHeight(55));
    else
    {
        readimagefile("C:\\User_Data\\asset\\myAccount.jpg",sWidth(45),sHeight(40),sWidth(55),sHeight(55));
        setbkcolor(RED);
        setcolor(WHITE);
        outtextxy(sWidth(53),sHeight(42),const_cast<char*>(totalMsg.c_str()));
        setcolor(RED);
        setbkcolor(backgroundColor);
    }
    readimagefile("C:\\User_Data\\asset\\feedback.jpg",sWidth(60),sHeight(40),sWidth(70),sHeight(55));
    readimagefile("C:\\User_Data\\asset\\aboutUs.jpg",sWidth(75),sHeight(40),sWidth(85),sHeight(55));
    settextjustify(CENTER_TEXT,TOP_TEXT);
    setcolor(BLACK);
    settextstyle(0,0,2);
    outtextxy(sWidth(20),sHeight(55),"[1]LEAF");
    outtextxy(sWidth(35),sHeight(55),"[2]READ");
    outtextxy(sWidth(50),sHeight(55),"[3]MY ACCOUNT");
    outtextxy(sWidth(65),sHeight(55),"[4]FEEDBACK");
    outtextxy(sWidth(80),sHeight(55),"[5]ABOUT US");
}

void Feedback(string user_loggedIn)
{
    cleardevice();
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    outtextxy(sWidth(50),sHeight(5),"USER FEEDBACKS");
    string fileName="C:\\User_Data\\asset\\reviews.txt";
    ifstream file(fileName);
    float lineNo, height = sHeight(20);
    std::string lines;
    bool hasReviewed=false;
    std::string searchString="<'"+user_loggedIn+"'>";
    while (getline(file, lines))
    {
        settextjustify(LEFT_TEXT, CENTER_TEXT);
        setcolor(BLACK);
        lineNo = print_Lines(sWidth(3), height, lines);
        height += lineNo;
        delay(10);
        ignoreInput();
        if (lines.find(searchString) != std::string::npos)
        {
            hasReviewed=true;
            file.close();
        }
    }
    file.close();
    if(!hasReviewed)
    {
        setcolor(BLACK);
        settextjustify(CENTER_TEXT,CENTER_TEXT);
        outtextxy(sWidth(50),sHeight(92),"Provide your Review on Us :[y/Y]");
        line(sWidth(0),sHeight(90),sWidth(100),sHeight(90));
        char sentMsg=getch();
        if(sentMsg=='y'||sentMsg=='Y')
        {
            string Message=userInput(sWidth(40),sHeight(95));
            string msgFile=fileName;
            ofstream msg(msgFile,ios::in|ios::app);
            msg<<"<'"<<user_loggedIn<<"'>"<< " Reviewed: "<<Message<<endl;
            setcolor(GREEN);
            settextjustify(CENTER_TEXT,CENTER_TEXT);
            outtextxy(sWidth(50),sHeight(98),"Thank you for your Feedback !");
            msg.close();
            getch();
            setcolor(BLACK);
        }
    }
    else{
        setcolor(BLACK);
        settextjustify(CENTER_TEXT,CENTER_TEXT);
        outtextxy(sWidth(50),sHeight(92),"Thank you for your Feedback !");
        line(sWidth(0),sHeight(90),sWidth(100),sHeight(90));
        getch();
    }

}

int main()
{
    initwindow(sWidth(100),sHeight(100),"Leaf Login-SignUp");
logOut:
    string loggedInUser=loginSignUp();
CHOICE:
    cleardevice();
    homePage(loggedInUser);
    char choice=getch();
    cleardevice();
    switch(choice)
    {
    case '1':
    {
        newSection User;
        User.setUser(loggedInUser);
        User.leafModule();
        goto CHOICE;
    }
    case '2':
    {
        readSection Read;
        Read.passUser(loggedInUser);
        Read.readModule();
        goto CHOICE;
    }
    case '3':
    {
        UserMgmt User;
        User.setUser(loggedInUser);
        bool logOut=User.AccountModule(loggedInUser);
        if(logOut)
            goto logOut;
        else
            goto CHOICE;
    }
    case '4':
    {
        Feedback(loggedInUser);
        goto CHOICE;
    }
    case '5':
    {
        cleardevice();
        readimagefile("C:\\User_Data\\asset\\teamLeaf.jpg",sWidth(0),sHeight(0),sWidth(100),sHeight(100));
        getch();
        goto CHOICE;
    }
    default:
    {
        delay(100);
        ignoreInput();
        goto CHOICE;
    }
    }
}

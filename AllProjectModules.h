#include<graphics.h>
#include<conio.h>
#include<string>
#include<fstream>
#include<iostream>
#include<ctime>
#include<algorithm>
#include<dirent.h>
#include<vector>

using namespace std;

class readSection
{
    string loggedInUser;
public:
    void passUser(string user)
    {
        loggedInUser=user;
    }
    int randomCall(string);
    void read_content(string, string);
    int search_author(string, string);
    void readModule();
};

// TO open the contents and sequential read..
void sequentialDisplay(string loggedInUser, string genre)
{
    string folderPath = "C:\\User_Data\\"+loggedInUser+"\\"+genre;
    string files[1000];
    DIR* dir;
    struct dirent* entry;
    dir = opendir(folderPath.c_str());
    int i=1;
    while ((entry = readdir(dir)) != nullptr)
    {
        if (entry->d_type == DT_REG)
        {
            files[i]=entry->d_name;
            i++;
        }
    }
    closedir(dir);
    int num = 1;
    while (num)
    {
        setfillstyle(SOLID_FILL,backgroundColor);
        bar(sWidth(1.5),sHeight(18),sWidth(98),sHeight(98));
        setcolor(BLACK);

        string fileName="C:\\User_Data\\"+loggedInUser+"\\"+genre+"\\"+files[num];
        ifstream file(fileName);

        if (!file)
        {
            settextjustify(CENTER_TEXT,CENTER_TEXT);
            outtextxy(sWidth(50),sHeight(60),"You Have Reached the End of Section");
            outtextxy(sWidth(50),sHeight(80),const_cast<char*>(files[num].c_str()));
            delay(500);
            getch();
            return;
        }
        string stories;
        int textHeight=0;

        while (file.good())
        {
            getline(file, stories);
            settextjustify(LEFT_TEXT,CENTER_TEXT);
            setcolor(BLACK);
            print_Lines(sWidth(2),sHeight(20)+textHeight,stories);
            textHeight+=textheight(const_cast<char*>(stories.c_str()));
            delay(50);
            ignoreInput();
        }
        file.close();


        readimagefile("C:\\User_Data\\asset\\prev.jpg",sWidth(5),sHeight(93),sWidth(15),sHeight(98));
        readimagefile("C:\\User_Data\\asset\\sback.jpg",sWidth(45),sHeight(93),sWidth(55),sHeight(98));
        readimagefile("C:\\User_Data\\asset\\next.jpg",sWidth(85),sHeight(93),sWidth(95),sHeight(98));
        char st = getch();
        if (st == '2')
            num++;
        else if (st == '1')
            num--;
        else if (st == '0')
            num = 0;
        else
            ignoreInput();
    }
}

int readSection:: randomCall(string filename)
{
    string errorMessage="Unable to open file";
    ifstream file(filename);
    if (!file.is_open())
    {
        outtextxy(100, 100, const_cast<char*>(errorMessage.c_str()));
        getch();
        exit(0);
    }
    string line;
    int sentenceCount = 0;

    while (getline(file, line))
    {
        sentenceCount++;
    }
    file.clear(); // Reset the file stream state
    file.seekg(0); // Rewind to the beginning of the file

    // Seed the random number generator
    srand(static_cast<unsigned int>(time(nullptr)));

    // Generate a random line number to select a sentence
    int randomLine = rand() % sentenceCount;

    // Skip to the selected line
    for (int i = 0; i < randomLine; i++)
    {
        getline(file, line);
    }
    file.close();
// Display the randomly selected sentence
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(6,0,3);
    setcolor(CYAN);
    rectangle(sWidth(35),sHeight(35),sWidth(65),sHeight(45));
    rectangle(sWidth(35.3),sHeight(35.5),sWidth(64.7),sHeight(44.5));
    setbkcolor(backgroundColor);
    outtextxy(sWidth(50),sHeight(40),"DO YOU KNOW ?!");
    setcolor(BLUE);
    int textHeight=print_Lines(sWidth(50),sHeight(45),line);
    return textHeight;
}

// TO open the contents and sequential read..
void readSection:: read_content(string folder, string genre)
{
    int num = 1;
    while (num)
    {
        setfillstyle(SOLID_FILL,backgroundColor);
        bar(sWidth(1.5),sHeight(18),sWidth(98),sHeight(98));
        if(folder=="Authors")
            bar(sWidth(1.5),sHeight(11.8),sWidth(98),sHeight(98));
        setcolor(BLACK);

        string filename = to_string(num);
        string destinationFile="C:\\User_Data\\"+loggedInUser+"\\Favourites\\"+genre+filename+".txt";
        ifstream file("C:\\User_Data\\asset\\" + folder + "\\" + genre + "\\" + filename+".txt");
        ifstream fav(destinationFile);
        if(fav.is_open())
            readimagefile("C:\\User_Data\\asset\\favadded.jpg",sWidth(94),sHeight(18),sWidth(96),sHeight(21));
        else
            readimagefile("C:\\User_Data\\asset\\favremoved.jpg",sWidth(94),sHeight(18),sWidth(96),sHeight(21));
        fav.close();

        if (!file)
        {
            settextjustify(CENTER_TEXT,CENTER_TEXT);
            outtextxy(sWidth(50),sHeight(60),"You Have Reached the End of Section");
            delay(500);
            getch();
            return;
        }
        string stories;
        int textHeight=0;

        if(folder=="Authors")
        {
            string imageFile="C:\\User_Data\\asset\\Authors\\"+filename+".jpg";
            readimagefile(const_cast<char*>(imageFile.c_str()),sWidth(85),sHeight(12),sWidth(97),sHeight(30));
        }

        while (file.good())
        {
            getline(file, stories);
            settextjustify(LEFT_TEXT,CENTER_TEXT);
            setcolor(BLACK);
            print_Lines(sWidth(2),sHeight(20)+textHeight,stories);
            textHeight+=textheight(const_cast<char*>(stories.c_str()));
            delay(50);
            ignoreInput();
        }
        file.close();


        readimagefile("C:\\User_Data\\asset\\prev.jpg",sWidth(5),sHeight(93),sWidth(15),sHeight(98));
        readimagefile("C:\\User_Data\\asset\\sback.jpg",sWidth(45),sHeight(93),sWidth(55),sHeight(98));
        readimagefile("C:\\User_Data\\asset\\next.jpg",sWidth(85),sHeight(93),sWidth(95),sHeight(98));
        char st = getch();
        if (st == '2')
            num++;
        else if (st == '1')
            num--;
        else if (st == '0')
            num = 0;
        else if(folder=="Contents"&&st=='3')
        {
            string destinationFolder="C:\\User_Data\\"+loggedInUser+"\\Favourites";
            mkdir((destinationFolder.c_str()));
            ifstream destination(destinationFile);
            if(destination.is_open())
            {
                destination.close();
                remove(destinationFile.c_str());
                readimagefile("C:\\User_Data\\asset\\favremoved.jpg",sWidth(94),sHeight(18),sWidth(96),sHeight(21));
            }
            else
            {
                string sourceFile="C:\\User_Data\\asset\\" + folder + "\\" + genre + "\\" + filename+".txt";
                ifstream source(sourceFile, ios::binary);
                ofstream destination(destinationFile,ios::binary);
                destination << source.rdbuf();
                destination.close();
                source.close();
                readimagefile("C:\\User_Data\\asset\\favadded.jpg",sWidth(94),sHeight(18),sWidth(96),sHeight(21));
            }

        }
        else
            ignoreInput();
    }
}


int readSection::search_author(string folder, string author)
{
    int num = 1,textHeight=0;
    string line, bio;
top:
    string filename = to_string(num);
    ifstream file("C:\\User_Data\\asset\\" + folder + "\\" + filename+".txt");
    if (file.is_open())
    {
        num++;
        getline(file, line);
        if (line.find(author) != string::npos)
        {
            setfillstyle(SOLID_FILL,backgroundColor);
            bar(sWidth(1.5),sHeight(18),sWidth(98),sHeight(98));
            if(folder=="Authors")
            {
                bar(sWidth(1.5),sHeight(11.8),sWidth(98),sHeight(98));
                string imageFile="C:\\User_Data\\asset\\Authors\\"+filename+".jpg";
                readimagefile(const_cast<char*>(imageFile.c_str()),sWidth(85),sHeight(12),sWidth(97),sHeight(30));
            }
            setcolor(BLACK);
            while (file.good())
            {
                getline(file, bio);
                settextjustify(LEFT_TEXT,CENTER_TEXT);
                setcolor(BLACK);
                print_Lines(sWidth(2),sHeight(20)+textHeight,bio);
                textHeight+=textheight(const_cast<char*>(bio.c_str()));
                delay(50);
                ignoreInput();
            }
            getch();
        }
        else
            goto top;
    }
    else
    {
        setcolor(RED);
        settextjustify(CENTER_TEXT,CENTER_TEXT);
        outtextxy(sWidth(50),sHeight(32),"Entered author is not found in our library !!");
        getch();
    }
}




void readSection::readModule()
{
TOP:
    setfillstyle(SOLID_FILL,backgroundColor);
    floodfill(0,0,backgroundColor);
    setbkcolor(backgroundColor);
    setlinestyle(0,0,2);

    int menuColor=RGB(77,77,77);
    readimagefile("C:\\User_Data\\asset\\menu.jpg",sWidth(9),sHeight(5),sWidth(12),sHeight(10));
    setfillstyle(SOLID_FILL,menuColor);
    bar(sWidth(15),sHeight(5),sWidth(30),sHeight(10));
    bar(sWidth(35),sHeight(5),sWidth(50),sHeight(10));
    bar(sWidth(55),sHeight(5),sWidth(70),sHeight(10));
    bar(sWidth(75),sHeight(5),sWidth(90),sHeight(10));

    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(10,0,2);
    setbkcolor(menuColor);
    setcolor(WHITE);
    outtextxy(sWidth(22.5),sHeight(8.5),"[1] Literature");
    outtextxy(sWidth(42.5),sHeight(8.5),"[2] Authors");
    outtextxy(sWidth(62.5),sHeight(8.5),"[3] Composed");
    outtextxy(sWidth(82.5),sHeight(8.5),"[4] Favorites");

    randomCall("C:\\User_Data\\asset\\Intro.txt");

    setcolor(BLACK);
    rectangle(sWidth(1),sHeight(11),sWidth(99),sHeight(99));
    rectangle(sWidth(1.3),sHeight(11.5),sWidth(98.7),sHeight(98.5));
    char choice=getch();
    setcolor(WHITE);
    switch(choice)
    {
    case '1':
CASE1:
        {
            setfillstyle(SOLID_FILL,backgroundColor);
            setbkcolor(backgroundColor);
            bar(sWidth(1.4),sHeight(11.6),sWidth(98.5),sHeight(98.3));          //clears the previous running outputs
            bar(sWidth(0.8),sHeight(6),sWidth(7.6),sHeight(16.1));           //clears icon on the top left (content icon)

            setcolor(BLACK);
            rectangle(sWidth(1),sHeight(11),sWidth(99),sHeight(99));
            rectangle(sWidth(1.3),sHeight(11.5),sWidth(98.7),sHeight(98.5));

            bar(sWidth(15),sHeight(5),sWidth(30),sHeight(10));          //For selected Effect
            rectangle(sWidth(15),sHeight(5),sWidth(30),sHeight(11));
            setcolor(backgroundColor);
            line(sWidth(15.1),sHeight(11),sWidth(29.9),sHeight(11));
            setcolor(BLACK);
            rectangle(sWidth(15.3),sHeight(5.5),sWidth(29.7),sHeight(11.5));
            setcolor(backgroundColor);
            line(sWidth(15.4),sHeight(11.5),sWidth(29.6),sHeight(11.5));

            settextjustify(CENTER_TEXT,CENTER_TEXT);
            settextstyle(10,0,2);
            setcolor(CYAN);
            outtextxy(sWidth(22.5),sHeight(10),"[1] Literature");

            readimagefile("C:\\User_Data\\asset\\stories.jpg",sWidth(15),sHeight(45),sWidth(25),sHeight(60));
            readimagefile("C:\\User_Data\\asset\\poems.jpg",sWidth(30),sHeight(45),sWidth(40),sHeight(60));
            readimagefile("C:\\User_Data\\asset\\dramas.jpg",sWidth(45),sHeight(45),sWidth(55),sHeight(60));
            readimagefile("C:\\User_Data\\asset\\jokes.jpg",sWidth(60),sHeight(45),sWidth(70),sHeight(60));
            readimagefile("C:\\User_Data\\asset\\back.jpg",sWidth(75),sHeight(45),sWidth(85),sHeight(60));

            char choice=getch();

            setfillstyle(SOLID_FILL,backgroundColor);
            bar(sWidth(1.4),sHeight(11.6),sWidth(98.5),sHeight(98.3));        //erases the icon and prepare display window.
            setcolor(BLACK);
            switch(choice)
            {
            case '1':
            {
                readimagefile("C:\\User_Data\\asset\\stories.jpg",sWidth(0.8),sHeight(6),sWidth(7.5),sHeight(16));
                read_content("Contents","Stories");
                goto CASE1;
            }
            case '2':
            {
                readimagefile("C:\\User_Data\\asset\\poems.jpg",sWidth(0.8),sHeight(6),sWidth(7.5),sHeight(16));
                read_content("Contents","Poems");
                goto CASE1;
            }
            case '3':
            {
                readimagefile("C:\\User_Data\\asset\\dramas.jpg",sWidth(0.8),sHeight(6),sWidth(7.5),sHeight(16));
                read_content("Contents","dramas");
                goto CASE1;
            }
            case '4':
            {
                readimagefile("C:\\User_Data\\asset\\jokes.jpg",sWidth(0.8),sHeight(6),sWidth(7.5),sHeight(16));
                read_content("Contents","jokes");
                goto CASE1;
            }
            case '5':
            {
                cleardevice();
                goto TOP;
            }
            default:
            {
                ignoreInput();
                goto CASE1;
            }
            }

        }
    case '2':
CASE2:
        {
            setfillstyle(SOLID_FILL,backgroundColor);
            setbkcolor(backgroundColor);
            setcolor(backgroundColor);
            bar(sWidth(1.4),sHeight(11.6),sWidth(98.5),sHeight(98.3));          //clears the previous running outputs
            bar(sWidth(35),sHeight(5),sWidth(50),sHeight(10));          //For selected Effect
            setcolor(BLACK);
            rectangle(sWidth(35),sHeight(5),sWidth(50),sHeight(11));
            setcolor(backgroundColor);
            line(sWidth(35.1),sHeight(11),sWidth(49.9),sHeight(11));
            setcolor(BLACK);
            rectangle(sWidth(35.3),sHeight(5.5),sWidth(49.7),sHeight(11.5));
            setcolor(backgroundColor);
            line(sWidth(35.4),sHeight(11.5),sWidth(49.6),sHeight(11.5));

            setcolor(CYAN);
            settextjustify(CENTER_TEXT,CENTER_TEXT);
            settextstyle(10,0,2);
            outtextxy(sWidth(42.5),sHeight(10),"[2] Authors");

            randomCall("C:\\User_Data\\asset\\authors.txt");
            readimagefile("C:\\User_Data\\asset\\searchBar.jpg",sWidth(33),sHeight(25),sWidth(67),sHeight(30));
            readimagefile("C:\\User_Data\\asset\\randomView.jpg",sWidth(85),sHeight(85),sWidth(98),sHeight(98));
            readimagefile("C:\\User_Data\\asset\\sback.jpg",sWidth(2),sHeight(94),sWidth(20),sHeight(98));
            settextjustify(CENTER_TEXT,CENTER_TEXT);
            settextstyle(10,0,2);
            setcolor(BLACK);
            outtextxy(sWidth(50),sHeight(28.5),"[1] SEARCH_FOR_AUTHOR");
            char choice=getch();

            switch(choice)
            {
            case '1':
            {
                settextjustify(LEFT_TEXT,CENTER_TEXT);
                outtextxy(sWidth(37),sHeight(28.5),"                          ");
                string authorName=getUserInput(sWidth(37),sHeight(28.5));
                transform(authorName.begin(), authorName.end(), authorName.begin(), ::toupper);
                search_author("Authors", authorName);
                goto CASE2;
            }
            case '2':
            {
                read_content("Authors","");
                goto CASE2;
            }
            case '0':
            {
                cleardevice();
                goto TOP;
            }
            default:
            {
                ignoreInput();
                goto CASE2;
            }
            }
        }
    case '3':
    {
        setfillstyle(SOLID_FILL,backgroundColor);
        setbkcolor(backgroundColor);
        setcolor(backgroundColor);
        bar(sWidth(1.4),sHeight(11.6),sWidth(98.5),sHeight(98.3));          //clears the previous running outputs
        bar(sWidth(55),sHeight(5),sWidth(70),sHeight(10));          //For selected Effect
        setcolor(BLACK);
        rectangle(sWidth(55),sHeight(5),sWidth(70),sHeight(11));
        setcolor(backgroundColor);
        line(sWidth(55.1),sHeight(11),sWidth(69.9),sHeight(11));
        setcolor(BLACK);
        rectangle(sWidth(55.3),sHeight(5.5),sWidth(69.7),sHeight(11.5));
        setcolor(backgroundColor);
        line(sWidth(55.4),sHeight(11.5),sWidth(69.6),sHeight(11.5));

        setcolor(CYAN);
        settextjustify(CENTER_TEXT,CENTER_TEXT);
        settextstyle(10,0,2);
        outtextxy(sWidth(62.5),sHeight(10),"[3] Composed");
        sequentialDisplay(loggedInUser,"Lits");
        cleardevice();
        goto TOP;
    }
    case '4':
    {
        setfillstyle(SOLID_FILL,backgroundColor);
        setbkcolor(backgroundColor);
        setcolor(backgroundColor);
        bar(sWidth(1.4),sHeight(11.6),sWidth(98.5),sHeight(98.3));          //clears the previous running outputs
        bar(sWidth(75),sHeight(5),sWidth(90),sHeight(10));          //For selected Effect
        setcolor(BLACK);
        rectangle(sWidth(75),sHeight(5),sWidth(90),sHeight(11));
        setcolor(backgroundColor);
        line(sWidth(75.1),sHeight(11),sWidth(89.9),sHeight(11));
        setcolor(BLACK);
        rectangle(sWidth(75.3),sHeight(5.5),sWidth(89.7),sHeight(11.5));
        setcolor(backgroundColor);
        line(sWidth(75.4),sHeight(11.5),sWidth(89.6),sHeight(11.5));

        settextjustify(CENTER_TEXT,CENTER_TEXT);
        settextstyle(10,0,2);
        setcolor(CYAN);
        outtextxy(sWidth(82.5),sHeight(10),"[4] Favorites");
        sequentialDisplay(loggedInUser,"Favourites");
        cleardevice();
        goto TOP;
    }
    case '0':
    {
        return ;
    }
    default:
    {
        cleardevice();
        goto TOP;
    }
    }
    getch();

}

/******************************************************************************************************
*********************END OF READ MODULES*********************************************************
****************************************************************************************************
---------------------------MY ACCOUNT MODULE-----------------------------------------------------
************************************************************************************************/


class myAccount
{
public:
    int aspectRatio=getmaxx()/getmaxy();
    int startxDisplay=sWidth(10);
    int startyDisplay=sHeight(50);
    int imageWidth=sWidth(10);
    int imageHeight=sWidth(10)/aspectRatio;
    int padding=sWidth(7);
    string loggedInUser;
public:
    void setUser(string User)
    {
        loggedInUser=User;
    }
    void displayMyAccount();
    void myNotes();
    void myMessages();
    void myAnalytics();
    void myTemplates();
};

void myAccount::displayMyAccount()
{
    readimagefile("C:\\User_Data\\asset\\myAccount.jpg",sWidth(35),sHeight(5),sWidth(39),sHeight(10));
    settextstyle(1,0,5);
    setbkcolor(backgroundColor);
    setcolor(BLACK);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    outtextxy(sWidth(52),sHeight(9.5),"My Account");
    settextstyle(0,0,2);
    readimagefile("C:\\User_Data\\asset\\myNotes.jpg",startxDisplay,startyDisplay,startxDisplay+imageWidth,startyDisplay+imageHeight);
    outtextxy((startxDisplay+startxDisplay+imageWidth)/2,startyDisplay+imageHeight+padding/2,"My Notes");

    readimagefile("C:\\User_Data\\asset\\myTemplates.jpg",startxDisplay+imageWidth+padding,startyDisplay,startxDisplay+2*imageWidth+padding,startyDisplay+imageHeight);
    outtextxy((2*startxDisplay+3*imageWidth+2*padding)/2,startyDisplay+imageHeight+padding/2,"My Templates");

    string checkFile="C:\\User_Data\\"+loggedInUser+"\\messages.txt";
    int msgCount=0;
    ifstream file(checkFile);
    if(file.is_open()){
        while(file.good()){
            string lineFile;
            getline(file,lineFile);
            msgCount++;
        }
    }
    file.close();
    string totalMsg=to_string(msgCount-1);
    if(msgCount==0)
    readimagefile("C:\\User_Data\\asset\\myRequests.jpg",startxDisplay+2*imageWidth+2*padding,startyDisplay,startxDisplay+3*imageWidth+2*padding,startyDisplay+imageHeight);
    else{
    readimagefile("C:\\User_Data\\asset\\myRequests.jpg",startxDisplay+2*imageWidth+2*padding,startyDisplay,startxDisplay+3*imageWidth+2*padding,startyDisplay+imageHeight);
        setbkcolor(RED);
        setcolor(WHITE);
        outtextxy((startxDisplay+3*imageWidth+2*padding)-sWidth(2),(startyDisplay)+sHeight(2),const_cast<char*>(totalMsg.c_str()));
        setcolor(BLACK);
        setbkcolor(backgroundColor);
    }
    outtextxy((2*startxDisplay+5*imageWidth+4*padding)/2,startyDisplay+imageHeight+padding/2,"My Notifications");

    readimagefile("C:\\User_Data\\asset\\myAnalytics.jpg",startxDisplay+3*imageWidth+3*padding,startyDisplay,startxDisplay+4*imageWidth+3*padding,startyDisplay+imageHeight);
    outtextxy((2*startxDisplay+7*imageWidth+6*padding)/2,startyDisplay+imageHeight+padding/2,"My Analytics");

    readimagefile("C:\\User_Data\\asset\\mySettings.jpg",startxDisplay+4*imageWidth+4*padding,startyDisplay,startxDisplay+5*imageWidth+4*padding,startyDisplay+imageHeight);
    outtextxy((2*startxDisplay+9*imageWidth+8*padding)/2,startyDisplay+imageHeight+padding/2,"Settings");
}

void displayFunction(string type, string loggedInUser)
{
choice1:
    cleardevice();
    if(type=="Notes")
        outtextxy(sWidth(50),sHeight(5),"My Notes");
    if(type=="Templates")
        outtextxy(sWidth(50),sHeight(5),"My Templates");
    string folderPath = "C:\\User_Data\\"+loggedInUser+"\\"+type;
    string files[1000];
    DIR* dir;
    struct dirent* entry;
    dir = opendir(folderPath.c_str());
    int i=0;
    while ((entry = readdir(dir)) != nullptr)
    {
        if (entry->d_type == DT_REG)
        {
            files[i]=entry->d_name;
            i++;
        }
    }
    closedir(dir);
    if(i!=0)
    {
        float height=sHeight(20);
        for(int j=0; j< i; j++)
        {
            int temp=j+1;
            char sN[100];
            sprintf(sN,"[%d]",temp);
            settextjustify(LEFT_TEXT,CENTER_TEXT);
            outtextxy(sWidth(40),height,sN);
            outtextxy(sWidth(45),height,const_cast<char*>(files[j].c_str()));
            height+=sHeight(5);
        }
        settextjustify(CENTER_TEXT,CENTER_TEXT);
    }
    else
    {
        outtextxy(sWidth(50),sHeight(50),"No any saved Files");
    }
    char choice=getch();
    int fileNo=choice-'0';
    if(fileNo>0&&fileNo<=i)
    {
        int selected=fileNo-1;
        string fileName="C:\\User_Data\\"+loggedInUser+"\\"+type+"\\"+files[selected];
        line(sWidth(0),sHeight(90),sWidth(100),sHeight(90));
        settextjustify(LEFT_TEXT,CENTER_TEXT);
        outtextxy(sWidth(35),sHeight(93),"FileName: ");
        outtextxy(sWidth(45),sHeight(93),const_cast<char*>(fileName.c_str()));
        outtextxy(sWidth(30),sHeight(97),"[1] Delete ");
        outtextxy(sWidth(65),sHeight(97),"[2] Open ");
        char subChoice=getch();
        setfillstyle(SOLID_FILL,backgroundColor);
        bar(sWidth(0),sHeight(90),sWidth(100),sHeight(100));
        switch(subChoice)
        {
        case '1':                       //remove file
        {
            remove(fileName.c_str());
            settextjustify(CENTER_TEXT,CENTER_TEXT);
            outtextxy(sWidth(50),sHeight(95),"File Deleted !!");
            getch();
            goto choice1;
        }
        case '2':                       // Open file in append mode;
        {
            string lines;
            float line, height = sHeight(20);

            cleardevice();

            // Open the file in input mode to read existing content
            ifstream infile(fileName);

            while (infile.good())
            {
                getline(infile, lines);
                settextjustify(LEFT_TEXT, CENTER_TEXT);
                setcolor(BLACK);
                line = print_Lines(sWidth(3), height, lines);
                height += line;
                delay(50);
                ignoreInput();
            }
            getch();
            infile.close();  // Close the file before reopening in output mode
            goto choice1;
        }

        default:
            goto choice1;
        }
    }
}

void myAccount::myNotes()
{
    cleardevice();
    displayFunction("Notes", loggedInUser);
}

void myAccount::myTemplates()
{
    cleardevice();
    displayFunction("Templates",loggedInUser);
}

class UserMgmt: public myAccount
{
public:
    void resetPassword();
    void resetProfile();
    void resetPIN();
    void resetName(string &name);
    void display();
    bool mySettings(string &name);
    bool AccountModule(string &name);
};

void UserMgmt::display()
{
    readimagefile("C:\\User_Data\\asset\\setting.jpg",sWidth(35),sHeight(5),sWidth(39),sHeight(10));
    settextstyle(1,0,5);
    setbkcolor(backgroundColor);
    setcolor(BLACK);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    outtextxy(sWidth(52),sHeight(9.5),"SETTINGS");
    settextstyle(0,0,2);
    readimagefile("C:\\User_Data\\asset\\changename.jpg",startxDisplay,startyDisplay,startxDisplay+imageWidth,startyDisplay+imageHeight);
    outtextxy((startxDisplay+startxDisplay+imageWidth)/2,startyDisplay+imageHeight+padding/2,"Change Nickname");

    readimagefile("C:\\User_Data\\asset\\changepass.jpg",startxDisplay+imageWidth+padding,startyDisplay,startxDisplay+2*imageWidth+padding,startyDisplay+imageHeight);
    outtextxy((2*startxDisplay+3*imageWidth+2*padding)/2,startyDisplay+imageHeight+padding/2,"Change Password");

    readimagefile("C:\\User_Data\\asset\\changeprofile.jpg",startxDisplay+2*imageWidth+2*padding,startyDisplay,startxDisplay+3*imageWidth+2*padding,startyDisplay+imageHeight);
    outtextxy((2*startxDisplay+5*imageWidth+4*padding)/2,startyDisplay+imageHeight+padding/2,"Change Image");

    readimagefile("C:\\User_Data\\asset\\resetPIN.jpg",startxDisplay+3*imageWidth+3*padding,startyDisplay,startxDisplay+4*imageWidth+3*padding,startyDisplay+imageHeight);
    outtextxy((2*startxDisplay+7*imageWidth+6*padding)/2,startyDisplay+imageHeight+padding/2,"Change PIN");

    readimagefile("C:\\User_Data\\asset\\logout.jpg",startxDisplay+4*imageWidth+4*padding,startyDisplay,startxDisplay+5*imageWidth+4*padding,startyDisplay+imageHeight);
    outtextxy((2*startxDisplay+9*imageWidth+8*padding)/2,startyDisplay+imageHeight+padding/2,"LogOut");
}

void UserMgmt::resetPassword()
{
    settextstyle(0,0,0);
    setfillstyle(SOLID_FILL,textBar);
    setcolor(textBar);
    string userProfile="C:\\User_Data\\"+loggedInUser+"\\userprofile.jpg";
    readimagefile(userProfile.c_str(),sWidth(42),sWidth(7), sWidth(58),sWidth(22));           //user icon
    roundBar(sWidth(28),sHeight(44),sWidth(38),sHeight(47),sWidth(0.5));    //System text to ask Age
    roundBar(sWidth(28),sHeight(51),sWidth(38),sHeight(54),sWidth(0.5));    //System text to ask Password
    roundBar(sWidth(28),sHeight(58),sWidth(38),sHeight(61),sWidth(0.5));    //System text to ask Password Confirmation

    setfillstyle(SOLID_FILL,inputBar);
    setcolor(inputBar);
    roundBar(sWidth(40),sHeight(44),sWidth(70),sHeight(47),sWidth(0.5));    //User Input to ask Old Password
    roundBar(sWidth(40),sHeight(51),sWidth(70),sHeight(54),sWidth(0.5));    //User INput to ask Password
    roundBar(sWidth(40),sHeight(58),sWidth(70),sHeight(61),sWidth(0.5));    //User Input to ask Password Confirmation

    settextjustify(CENTER_TEXT,CENTER_TEXT);
    setbkcolor(textBar);
    setcolor(RED);
    outtextxy(sWidth(33),sHeight(46),"Old Password :");
    outtextxy(sWidth(33),sHeight(53),"New Password :");
    outtextxy(sWidth(33),sHeight(60),"Confirmation :");

    string oldPassword, newPassword, confirmedNew;
    string fileName="C:\\User_Data\\"+loggedInUser+"\\profile.txt";
    string fileUser, filePassword, fileContents;

    ifstream file(fileName);
    file>>fileUser>>filePassword;
    file.close();

    setcolor(BLACK);
    line(sWidth(42),sHeight(47.6),sWidth(68),sHeight(47.6));        //Gives Active Box effect by a black line.
    setcolor(RED);
    oldPassword=getpassword(sWidth(55),sHeight(46),false);
    setcolor(inputBar);
    line(sWidth(42),sHeight(47.6),sWidth(68),sHeight(47.6));        //Removes Active Box effect by a black line.
    setcolor(RED);
    if(oldPassword!=filePassword)
    {
        readimagefile("C:\\User_Data\\asset\\warning.jpg",sWidth(68),sHeight(44),sWidth(70),sHeight(47));
        outtextxy(sWidth(55),sHeight(46),"Password Not Matched");
        getch();
        delay(200);
        ignoreInput();
        cleardevice();
        return ;
    }
    else
    {
        readimagefile("C:\\User_Data\\asset\\verified.jpg",sWidth(68),sHeight(44),sWidth(70),sHeight(47));
    }

    setcolor(BLACK);
    line(sWidth(42),sHeight(54.6),sWidth(68),sHeight(54.6));        //Gives Active Box effect by a black line.
    setcolor(RED);
    newPassword=getpassword(sWidth(55),sHeight(53),true);
    setcolor(inputBar);
    line(sWidth(42),sHeight(54.6),sWidth(68),sHeight(54.6));        //Gives Active Box effect by a black line.
    setcolor(RED);
    if(newPassword==oldPassword)
    {
        readimagefile("C:\\User_Data\\asset\\warning.jpg",sWidth(68),sHeight(51),sWidth(70),sHeight(54));
        outtextxy(sWidth(55),sHeight(53),"Error; Same as Old Password");
        getch();
        delay(200);
        ignoreInput();
        cleardevice();
        return ;
    }
    else
    {
        readimagefile("C:\\User_Data\\asset\\verified.jpg",sWidth(68),sHeight(51),sWidth(70),sHeight(54));
    }

    setcolor(BLACK);
    line(sWidth(42),sHeight(61.6),sWidth(68),sHeight(61.6));        //Gives Active Box effect by a black line.
    setcolor(RED);
    confirmedNew=getpassword(sWidth(55),sHeight(60),false);
    setcolor(inputBar);
    line(sWidth(42),sHeight(61.6),sWidth(68),sHeight(61.6));        //Gives Active Box effect by a black line.
    setcolor(RED);
    if(newPassword!=confirmedNew)
    {
        readimagefile("C:\\User_Data\\asset\\warning.jpg",sWidth(68),sHeight(58),sWidth(70),sHeight(61));
        outtextxy(sWidth(55),sHeight(60),"Password Not Matched !");
        getch();
        delay(200);
        ignoreInput();
        cleardevice();
        return ;
    }
    else
    {
        readimagefile("C:\\User_Data\\asset\\verified.jpg",sWidth(68),sHeight(58),sWidth(70),sHeight(61));
    }

    editString(fileName,oldPassword,newPassword);
    setcolor(GREEN);
    outtextxy(sWidth(50),sHeight(85),"PassWord Changed SuccessFully. ");
    getch();
    setcolor(RED);
}

void UserMgmt::resetProfile()
{
    string finalImage="C:\\User_Data\\"+loggedInUser+"\\userprofile.jpg";
    string profileImage=profileLocation();
    if(profileImage.empty())
    {
        outtextxy(sWidth(50),sHeight(85),"No Image Selected. ");
        delay(100);
        getch();
        outtextxy(sWidth(50),sHeight(85),"                                  ");
    }
    else
    {
        copyImage(profileImage,finalImage);
        setcolor(GREEN);
        outtextxy(sWidth(50),sHeight(85),"Profile Image Changed Successfully !!");
        delay(100);
        getch();
        outtextxy(sWidth(50),sHeight(85),"                                                  ");
        setcolor(RED);
    }
}

void UserMgmt::resetPIN()
{
    settextstyle(0,0,0);
    setfillstyle(SOLID_FILL,textBar);
    setcolor(textBar);
    string userProfile="C:\\User_Data\\"+loggedInUser+"\\userprofile.jpg";
    readimagefile(userProfile.c_str(),sWidth(42),sWidth(7), sWidth(58),sWidth(22));           //user icon
    roundBar(sWidth(28),sHeight(44),sWidth(38),sHeight(47),sWidth(0.5));    //System text to ask Old PIN
    roundBar(sWidth(28),sHeight(51),sWidth(38),sHeight(54),sWidth(0.5));    //System text to ask New PIN
    roundBar(sWidth(28),sHeight(58),sWidth(38),sHeight(61),sWidth(0.5));    //System text to ask PIN Confirmation

    setfillstyle(SOLID_FILL,inputBar);
    setcolor(inputBar);
    roundBar(sWidth(40),sHeight(44),sWidth(70),sHeight(47),sWidth(0.5));    //User Input to ask Old Password
    roundBar(sWidth(40),sHeight(51),sWidth(70),sHeight(54),sWidth(0.5));    //User INput to ask Password
    roundBar(sWidth(40),sHeight(58),sWidth(70),sHeight(61),sWidth(0.5));    //User Input to ask Password Confirmation

    settextjustify(CENTER_TEXT,CENTER_TEXT);
    setbkcolor(textBar);
    setcolor(RED);
    outtextxy(sWidth(33),sHeight(46),"Old PIN :");
    outtextxy(sWidth(33),sHeight(53),"New PIN :");
    outtextxy(sWidth(33),sHeight(60),"Confirmation :");

    string oldPIN, newPIN, confirmedNew;
    string fileName="C:\\User_Data\\"+loggedInUser+"\\profile.txt";
    string fileUser, filepassword,  filePIN, fileContents;

    ifstream file(fileName);
    file>>fileUser>>filepassword>>filePIN;
    file.close();

    setcolor(BLACK);
    line(sWidth(42),sHeight(47.6),sWidth(68),sHeight(47.6));        //Gives Active Box effect by a black line.
    setcolor(RED);
    oldPIN=resetCode(sWidth(55),sHeight(46));
    setcolor(inputBar);
    line(sWidth(42),sHeight(47.6),sWidth(68),sHeight(47.6));        //Removes Active Box effect by a black line.
    setcolor(RED);
    if(oldPIN!=filePIN)
    {
        readimagefile("C:\\User_Data\\asset\\warning.jpg",sWidth(68),sHeight(44),sWidth(70),sHeight(47));
        outtextxy(sWidth(55),sHeight(46),"PIN Not Matched");
        getch();
        delay(200);
        ignoreInput();
        cleardevice();
        return ;
    }
    else
    {
        readimagefile("C:\\User_Data\\asset\\verified.jpg",sWidth(68),sHeight(44),sWidth(70),sHeight(47));
    }

    setcolor(BLACK);
    line(sWidth(42),sHeight(54.6),sWidth(68),sHeight(54.6));        //Gives Active Box effect by a black line.
    setcolor(RED);
    newPIN=resetCode(sWidth(55),sHeight(53));
    setcolor(inputBar);
    line(sWidth(42),sHeight(54.6),sWidth(68),sHeight(54.6));        //Gives Active Box effect by a black line.
    setcolor(RED);
    if(newPIN==oldPIN)
    {
        readimagefile("C:\\User_Data\\asset\\warning.jpg",sWidth(68),sHeight(51),sWidth(70),sHeight(54));
        outtextxy(sWidth(55),sHeight(53),"Error; Same as Old PIN");
        getch();
        delay(200);
        ignoreInput();
        cleardevice();
        return ;
    }
    else
    {
        readimagefile("C:\\User_Data\\asset\\verified.jpg",sWidth(68),sHeight(51),sWidth(70),sHeight(54));
    }

    setcolor(BLACK);
    line(sWidth(42),sHeight(61.6),sWidth(68),sHeight(61.6));        //Gives Active Box effect by a black line.
    setcolor(RED);
    confirmedNew=resetCode(sWidth(55),sHeight(60));
    setcolor(inputBar);
    line(sWidth(42),sHeight(61.6),sWidth(68),sHeight(61.6));        //Gives Active Box effect by a black line.
    setcolor(RED);
    if(newPIN!=confirmedNew)
    {
        readimagefile("C:\\User_Data\\asset\\warning.jpg",sWidth(68),sHeight(58),sWidth(70),sHeight(61));
        outtextxy(sWidth(55),sHeight(60),"PIN not matched !");
        getch();
        delay(200);
        ignoreInput();
        cleardevice();
        return ;
    }
    else
    {
        readimagefile("C:\\User_Data\\asset\\verified.jpg",sWidth(68),sHeight(58),sWidth(70),sHeight(61));
    }

    editString(fileName,oldPIN,newPIN);
    setcolor(GREEN);
    outtextxy(sWidth(50),sHeight(85),"Reset PIN Changed SuccessFully. ");
    getch();
    setcolor(RED);
}

void UserMgmt::resetName(string &changeName)
{
    settextstyle(0,0,0);
    setfillstyle(SOLID_FILL,textBar);
    setcolor(textBar);
    string userProfile="C:\\User_Data\\"+loggedInUser+"\\userprofile.jpg";
    readimagefile(userProfile.c_str(),sWidth(42),sWidth(7), sWidth(58),sWidth(22));           //user icon
    roundBar(sWidth(28),sHeight(44),sWidth(38),sHeight(47),sWidth(0.5));    //System text to ask Old Name
    roundBar(sWidth(28),sHeight(51),sWidth(38),sHeight(54),sWidth(0.5));    //System text to ask PIN
    roundBar(sWidth(28),sHeight(58),sWidth(38),sHeight(61),sWidth(0.5));    //System text to ask NewName

    setfillstyle(SOLID_FILL,inputBar);
    setcolor(inputBar);
    roundBar(sWidth(40),sHeight(44),sWidth(70),sHeight(47),sWidth(0.5));    //User Input to ask Old Name
    roundBar(sWidth(40),sHeight(51),sWidth(70),sHeight(54),sWidth(0.5));    //User INput to ask PIN
    roundBar(sWidth(40),sHeight(58),sWidth(70),sHeight(61),sWidth(0.5));    //User Input to ask New Name

    settextjustify(CENTER_TEXT,CENTER_TEXT);
    setbkcolor(textBar);
    setcolor(RED);
    outtextxy(sWidth(33),sHeight(46),"Nickname :");
    outtextxy(sWidth(33),sHeight(53),"PIN :");
    outtextxy(sWidth(33),sHeight(60),"New Nickname :");

    setbkcolor(inputBar);
    string oldName, newName, PIN;
    string fileName="C:\\User_Data\\"+loggedInUser+"\\profile.txt";
    string fileUser, filepassword,  filePIN, fileContents;

    ifstream file(fileName);
    file>>fileUser>>filepassword>>filePIN;
    file.close();

    setcolor(BLACK);
    line(sWidth(42),sHeight(47.6),sWidth(68),sHeight(47.6));        //Gives Active Box effect by a black line.
    setcolor(RED);
    oldName=userInput(sWidth(55),sHeight(46));
    setcolor(inputBar);
    line(sWidth(42),sHeight(47.6),sWidth(68),sHeight(47.6));        //Removes Active Box effect by a black line.
    setcolor(RED);
    if(oldName!=fileUser)
    {
        readimagefile("C:\\User_Data\\asset\\warning.jpg",sWidth(68),sHeight(44),sWidth(70),sHeight(47));
        outtextxy(sWidth(55),sHeight(46),"Invalid UserName !");
        getch();
        delay(200);
        ignoreInput();
        cleardevice();
        return ;
    }
    else
    {
        readimagefile("C:\\User_Data\\asset\\verified.jpg",sWidth(68),sHeight(44),sWidth(70),sHeight(47));
    }

    setcolor(BLACK);
    line(sWidth(42),sHeight(54.6),sWidth(68),sHeight(54.6));        //Gives Active Box effect by a black line.
    setcolor(RED);
    PIN=resetCode(sWidth(55),sHeight(53));
    setcolor(inputBar);
    line(sWidth(42),sHeight(54.6),sWidth(68),sHeight(54.6));        //Gives Active Box effect by a black line.
    setcolor(RED);
    if(PIN!=filePIN)
    {
        readimagefile("C:\\User_Data\\asset\\warning.jpg",sWidth(68),sHeight(51),sWidth(70),sHeight(54));
        outtextxy(sWidth(55),sHeight(53),"PIN not matched");
        getch();
        delay(200);
        ignoreInput();
        cleardevice();
        return ;
    }
    else
    {
        readimagefile("C:\\User_Data\\asset\\verified.jpg",sWidth(68),sHeight(51),sWidth(70),sHeight(54));
    }
ChangeName:
    setcolor(BLACK);
    line(sWidth(42),sHeight(61.6),sWidth(68),sHeight(61.6));        //Gives Active Box effect by a black line.
    setcolor(RED);
    newName=userInput(sWidth(55),sHeight(60));
    setcolor(inputBar);
    line(sWidth(42),sHeight(61.6),sWidth(68),sHeight(61.6));        //Gives Active Box effect by a black line.
    setcolor(RED);
    DIR *dir = opendir(("C:\\User_Data\\" + newName).c_str());
    if(newName==oldName||newName.length()<minHandle||newName.length()>32||newName.find(' ')!=string::npos||dir)
    {
        readimagefile("C:\\User_Data\\asset\\warning.jpg",sWidth(68),sHeight(58),sWidth(70),sHeight(61));
        if(newName==oldName)
            outtextxy(sWidth(55),sHeight(60),"Same as old UserName !");
        if(newName.length()<minHandle||newName.length()>32)
            outtextxy(sWidth(55),sHeight(60),"Character Limit (3 - 32)");
        if(newName.find(' ')!=string::npos)
            outtextxy(sWidth(55),sHeight(60),"Contains Space: Invalid Character");
        if(dir)
            outtextxy(sWidth(55),sHeight(60),"LeafHandle Already Taken !!");
        getch();
        delay(200);
        ignoreInput();
        bar(sWidth(40),sHeight(58.1),sWidth(70),sHeight(60.9));
        goto ChangeName;
    }
    else
    {
        readimagefile("C:\\User_Data\\asset\\verified.jpg",sWidth(68),sHeight(58),sWidth(70),sHeight(61));
    }

    editString(fileName,oldName,newName);
    string oldFolderName = "C:\\User_Data\\"+loggedInUser;
    string newFolderName = "C:\\User_Data\\"+newName;

    rename(oldFolderName.c_str(), newFolderName.c_str());

    setcolor(GREEN);
    loggedInUser=newName;
    changeName=newName;
    outtextxy(sWidth(50),sHeight(85),"LeafHandle Changed SuccessFully. ");
    getch();
    setcolor(RED);
}

bool UserMgmt::mySettings(string &changeName)
{
displaySettings:
    setfillstyle(SOLID_FILL,backgroundColor);
    floodfill(0,0,backgroundColor);

    setcolor(GREEN);
    setlinestyle(SOLID_LINE,SOLID_FILL,3);
    rectangle(sWidth(0.1),sHeight(0.2),sWidth(99.9),sHeight(99.8));
    rectangle(sWidth(0.5),sHeight(0.8),sWidth(99.5),sHeight(99.2));
    setlinestyle(0,0,0);
    setcolor(RED);
    display();
    DIR *dir = opendir(("C:\\User_Data\\" + loggedInUser).c_str());
    closedir(dir);

    char userChoice=getch();
    if(dir)
    {
        closedir(dir);
        switch(userChoice)
        {
        case '1':                           //Change Nickname
        {
            cleardevice();
            resetName(changeName);
            cleardevice();
            goto displaySettings;
        }
        case '2':                           //Change Password
        {
            cleardevice();
            resetPassword();
            cleardevice();
            goto displaySettings;
        }
        case '3':                           //Change Image
        {
            resetProfile();
            goto displaySettings;
        }
        case '4':                           //Change PIN
        {
            cleardevice();
            resetPIN();
            cleardevice();
            goto displaySettings;
        }
        case '5':                           //Logout
        {
            cleardevice();
            return true;
        }
        case '0':
        {
            cleardevice();
            return false;
        }
        default:
        {
            delay(100);
            ignoreInput();
            goto displaySettings;
        }
        }
    }
    else
    {
        cleardevice();
        outtextxy(sWidth(50),sHeight(50),"No User Logged In");
        getch();
        exit(0);
    }
}

void myAccount::myMessages()
{
    cleardevice();
settextjustify(CENTER_TEXT,CENTER_TEXT);
setcolor(BLACK);
outtextxy(sWidth(50),sHeight(5),"MY MESSAGES");

    string lines;
    float line, height = sHeight(20);

    string fileName="C:\\User_Data\\"+loggedInUser+"\\messages.txt";
    // Open the file in input mode to read existing content
    ifstream infile(fileName);

    while (infile.good())
    {
        getline(infile, lines);
        settextjustify(LEFT_TEXT, CENTER_TEXT);
        setcolor(BLACK);
        line = print_Lines(sWidth(3), height, lines);
        height += line;
        delay(50);
        ignoreInput();
    }
    infile.close();  // Close the file before reopening in output mode
    remove(fileName.c_str());
    getch();
}

void drawbox(int l, int b) {
    int xc = getmaxx() / 2;
    int yc = getmaxy() / 2;
    rectangle(xc - l, yc - b, xc + l, yc + b);
}

void generateBarGraph(char names[][20], int values[]) {
    settextstyle(0,0,0);
    int xc = getmaxx() / 2;
    int yc = getmaxy() / 2;
    float pixeldiv = 30, scalediv = 2, barwidth = 80, bargap = 80;
    int data = 5;
     char yaxis[20] = "Number", xaxis[20] = "Category", title[50] = "My Analytics";

    cleardevice();
    outtextxy(xc - strlen(title), yc - 210, title);
    drawbox(600, 400);
    setcolor(2);
    drawbox(602, 402);
    line(xc - 500, yc + 280, xc + 550, yc + 280);
    line(xc - 500, yc + 280, xc - 500, yc - 280);
    int px = xc - 520, py = yc + 260;
    for (int i = 0; i <= 15; i++) {
        char num[10];
        itoa(scalediv * (i + 1), num, 10);
        line(px, py, px + 4, py);
        outtextxy(px - strlen(num) * 8, py - 5, num);
        py = py - pixeldiv;
    }
    settextstyle(1, 0, 1);
    outtextxy(xc + 300, yc + 340, xaxis);
    settextstyle(1, 1, 1);
    outtextxy(xc - 560, yc - 60, yaxis);
    int xb = xc - 450, yb = yc + 280;
    int lx = xc - 500, ly = yc + 280;
    for (int i = 0; i < data; i++) {
        float height = (pixeldiv / scalediv) * values[i];
        setfillstyle(1, i + 1);
        bar(xb, yb, xb + barwidth, yb - height);
        line(lx, ly, xb + barwidth / 2, yb - height);
        lx = xb + barwidth / 2;
        ly = yb - height;
        settextstyle(1, 0, 1);
        outtextxy(xb + 5, yb + 10, names[i]);
        xb = xb + barwidth + bargap;
    }
}


int countFilesInDirectory(const std::string& path) {
    DIR* dir = opendir(path.c_str());
    if (dir == nullptr) {
        std::cerr << "Error opening directory: " << path << std::endl;
        return -1; // Error opening directory
    }

    int fileCount = 0;
    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_REG) {  // Check if it's a regular file
            fileCount++;
        }
    }

    closedir(dir);
    return fileCount;
}


void myAccount::myAnalytics(){
    char Tagnames[5][20] = {"Notes", "Lits", "Templates", "Tags", "Genres"};
    string noteFile="C:\\User_Data\\"+loggedInUser+"\\notes";
    int totalNotes=countFilesInDirectory(noteFile);

    string litsFile="C:\\User_Data\\"+loggedInUser+"\\Lits";
    int totalLits=countFilesInDirectory(litsFile);

    string templeteFile="C:\\User_Data\\"+loggedInUser+"\\Templates";
    int totalTemplete=countFilesInDirectory(templeteFile);

    string tagsFile="C:\\User_Data\\"+loggedInUser+"\\Tags";
    int totalTags=countFilesInDirectory(tagsFile);

    string genreFile="C:\\User_Data\\"+loggedInUser+"\\Genre";
    int totalGenre=countFilesInDirectory(genreFile);

    int values[5] = {totalNotes,totalLits,totalTemplete,totalTags,totalGenre};

    generateBarGraph(Tagnames, values);
    getch();
}


bool UserMgmt::AccountModule(string &changeName)
{
myAccount:
    setfillstyle(SOLID_FILL,backgroundColor);
    floodfill(0,0,backgroundColor);

    setcolor(GREEN);
    setlinestyle(SOLID_LINE,SOLID_FILL,3);
    rectangle(sWidth(0.1),sHeight(0.2),sWidth(99.9),sHeight(99.8));
    rectangle(sWidth(0.5),sHeight(0.8),sWidth(99.5),sHeight(99.2));
    setlinestyle(0,0,0);
    setcolor(RED);
    displayMyAccount();
    DIR *dir = opendir(("C:\\User_Data\\" + loggedInUser).c_str());
    closedir(dir);
    char userChoice=getch();
    if(dir)
    {
        switch(userChoice)
        {
        case '1':                           //Change Nickname
        {
            cleardevice();
            myNotes();
            cleardevice();
            goto myAccount;
        }
        case '2':                           //Change Password
        {
            cleardevice();
            myTemplates();
            cleardevice();
            goto myAccount;
        }
        case '3':                           //Change Image
        {
            myMessages();
            cleardevice();
            goto myAccount;
        }
        case '4':                           //Change PIN
        {
            cleardevice();
            myAnalytics();
            cleardevice();
            goto myAccount;
        }
        case '5':                           //Logout
        {
            cleardevice();
            bool logOut=mySettings(changeName);
            if(logOut)
                return true;
            else
                goto myAccount;
        }
        case '0':
        {
            cleardevice();
            return false;
        }
        default:
        {
            delay(100);
            ignoreInput();
            goto myAccount;
        }
        }
    }
    else
    {
        cleardevice();
        outtextxy(sWidth(50),sHeight(50),"No User Logged In");
        getch();
        exit(0);
    }
}

/*************************************************************************************************************************
----------------------------------MY ACCOUNT MODULE ENDED--------------------------------------------------------------
**************************************************************************************************************************
-------------------------------------LEAF MODULE (NOTES-LITS) BEGINS------------------------------------------------------
*************************************************************************************************************************/

class newSection
{
public:
    int aspectRatio=getmaxx()/getmaxy();
    int startxDisplay=sWidth(10);
    int startyDisplay=sHeight(50);
    int imageWidth=sWidth(10);
    int imageHeight=sWidth(10)/aspectRatio;
    int padding=sWidth(7);
    string loggedInUser;
public:
    void setUser(string User)
    {
        loggedInUser=User;
    }
    void displaySection();
    void writeNotes();
    void createTemplate();
    void createLit();
    void myTags();
    void myGenres();
    void leafModule();
};

void newSection::displaySection()
{
    readimagefile("C:\\User_Data\\asset\\new.jpg",sWidth(35),sHeight(5),sWidth(39),sHeight(10));
    settextstyle(1,0,5);
    setbkcolor(backgroundColor);
    setcolor(BLACK);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    outtextxy(sWidth(52),sHeight(9.5),"LEAF");
    settextstyle(0,0,2);
    readimagefile("C:\\User_Data\\asset\\myNotes.jpg",startxDisplay,startyDisplay,startxDisplay+imageWidth,startyDisplay+imageHeight);
    outtextxy((startxDisplay+startxDisplay+imageWidth)/2,startyDisplay+imageHeight+padding/2," Create Notes");

    readimagefile("C:\\User_Data\\asset\\myTemplates.jpg",startxDisplay+imageWidth+padding,startyDisplay,startxDisplay+2*imageWidth+padding,startyDisplay+imageHeight);
    outtextxy((2*startxDisplay+3*imageWidth+2*padding)/2,startyDisplay+imageHeight+padding/2,"Create Templates");

    readimagefile("C:\\User_Data\\asset\\myLits.jpg",startxDisplay+2*imageWidth+2*padding,startyDisplay,startxDisplay+3*imageWidth+2*padding,startyDisplay+imageHeight);
    outtextxy((2*startxDisplay+5*imageWidth+4*padding)/2,startyDisplay+imageHeight+padding/2,"Lit");

    readimagefile("C:\\User_Data\\asset\\myTags.jpg",startxDisplay+3*imageWidth+3*padding,startyDisplay,startxDisplay+4*imageWidth+3*padding,startyDisplay+imageHeight);
    outtextxy((2*startxDisplay+7*imageWidth+6*padding)/2,startyDisplay+imageHeight+padding/2,"Tags");

    readimagefile("C:\\User_Data\\asset\\myGenres.jpg",startxDisplay+4*imageWidth+4*padding,startyDisplay,startxDisplay+5*imageWidth+4*padding,startyDisplay+imageHeight);
    outtextxy((2*startxDisplay+9*imageWidth+8*padding)/2,startyDisplay+imageHeight+padding/2,"Genres");
}


string WriteInConsole(int n, float height, string prev)
{
    string Content=prev;
    while(true)
    {
        ofstream file("temp.txt");
        char ch=getch();
        if(ch == 19 && (GetAsyncKeyState(VK_CONTROL)))
        {
            break;
        }
        if(isalnum(ch)||ispunct(ch))
            Content+=ch;
        if(ch==' ')
            Content+=" ";
        if(ch==13)
        {
            Content+="\n";
        }
        if(!Content.empty()&&ch=='\b')
        {
            Content.pop_back();
        }
        file<<Content;
        file.close();
        settextjustify(LEFT_TEXT,CENTER_TEXT);
        setfillstyle(SOLID_FILL,backgroundColor);
        bar(sWidth(2),height-sHeight(2),sWidth(99),sHeight(99));
        displayLastNLines("temp.txt",n,height);
        file.close();
        remove("temp.txt");
    }
    return Content;
}

void newSection:: writeNotes()
{
    setbkcolor(backgroundColor);
    settextstyle(0,0,2);
    setcolor(GREEN);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    outtextxy(sWidth(50),sHeight(5),"Seize the Now, Save the Forever: Notes Unedited, Moments Preserved");
    line(sWidth(12),sHeight(5.2),sWidth(88),sHeight(5.2));
    setcolor(BLACK);
    line(sWidth(10),sHeight(5.5),sWidth(90),sHeight(5.5));
    setcolor(RED);
    outtextxy(sWidth(15),sHeight(10),"Date: [YYYY-MM-DD]");
date:
    string date=userInput(sWidth(15),sHeight(13));
    bool isValid=isDateValid(date);
    if(!isValid)
    {
        outtextxy(sWidth(15),sHeight(13),"                                                           ");
        outtextxy(sWidth(15),sHeight(13),"Invalid Date");
        getch();
        outtextxy(sWidth(15),sHeight(13),"                                                           ");
        goto date;
    }

    setcolor(BLACK);
    line(sWidth(45),sHeight(13),sWidth(88),sHeight(13));
    line(sWidth(45),sHeight(13.3),sWidth(88),sHeight(13.3));
    outtextxy(sWidth(50),sHeight(12.5),"Title: ");
    string title=userInput(sWidth(70),sHeight(12.5));
    float height=sHeight(30);
    string Content=WriteInConsole(3,sHeight(30),"");
    if(Content.empty())
    {
        settextjustify(CENTER_TEXT,CENTER_TEXT);
        setcolor(RED);
        outtextxy(sWidth(50),sHeight(83),"Empty Note Discarded !!");
        getch();
        setcolor(BLACK);
    }
    else
    {
        string fileName="C:/User_Data/"+loggedInUser+"/Notes/"+title+".txt";
        ofstream file(fileName);
        if(file.is_open())
        {
            file<<date<<endl;
            file<<title<<endl;
            file<<Content<<endl;
            file<<"*******************************************************************"<<endl;
            file.close();
            settextjustify(CENTER_TEXT,CENTER_TEXT);
            setcolor(GREEN);
            outtextxy(sWidth(50),sHeight(83),"Note Saved Successfully !!");
            getch();
            setcolor(BLACK);
        }
        else
            outtextxy(100,200,"Error");
    }
}

void newSection::createTemplate()
{
    string filename;
    string advertiser, position, department, advertisement, experience, qualification, institution, name;
    readimagefile("C:\\User_Data\\asset\\template.jpg",sWidth(35),sHeight(5),sWidth(39),sHeight(10));
    settextstyle(1,0,5);
    setbkcolor(backgroundColor);
    setcolor(BLACK);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    outtextxy(sWidth(52),sHeight(9.5),"TEMPLATE");
    settextstyle(0,0,2);
    outtextxy(sWidth(50),sHeight(30),"[1]. Job Application (Sample I)");
    outtextxy(sWidth(50),sHeight(40),"MORE TO BE ADDED......");
templete:
    char ch=getch();
    if(ch=='1')
    {
        cleardevice();
        outtextxy(sWidth(30),sHeight(30),"Name of Hiring Manager: ");
        advertiser=userInput(sWidth(65),sHeight(30));
        outtextxy(sWidth(30),sHeight(35),"Vacant Position: ");
        position=userInput(sWidth(65),sHeight(35));
        outtextxy(sWidth(30),sHeight(40),"Name of Department: ");
        department=userInput(sWidth(65),sHeight(40));
        outtextxy(sWidth(30),sHeight(45),"Vacancy Published In: ");
        advertisement=userInput(sWidth(65),sHeight(45));
        outtextxy(sWidth(30),sHeight(50),"Years of Experience: ");
        experience=userInput(sWidth(65),sHeight(50));
        outtextxy(sWidth(30),sHeight(55),"Qualification: ");
        qualification=userInput(sWidth(65),sHeight(55));
        outtextxy(sWidth(30),sHeight(60),"Graduated From: ");
        institution=userInput(sWidth(65),sHeight(60));
        outtextxy(sWidth(30),sHeight(65),"Applicant's Name: ");
        name=userInput(sWidth(65),sHeight(65));
        outtextxy(sWidth(30),sHeight(70),"Save As (File Name): ");
        filename=userInput(sWidth(65),sHeight(70));
        string filepath="C:\\User_Data\\"+loggedInUser+"\\Templates\\"+filename+".txt";
        ifstream file("C:\\User_Data\\asset\\application1.txt");
        ofstream outfile(filepath);
        while(file.good())
        {
            string fileContent;
            getline(file,fileContent);
            outfile<<fileContent<<endl;
        }
        file.close();
        outfile.close();
        editString(filepath,"[advertiser]",advertiser);
        editString(filepath,"[position]",position);
        editString(filepath,"[dept]",department);
        editString(filepath,"[dept]",department);
        editString(filepath,"[advertisement]",advertisement);
        editString(filepath,"[experience]",experience);
        editString(filepath,"[qualification]",qualification);
        editString(filepath,"[institution]",institution);
        editString(filepath,"[name]",name);
        setcolor(GREEN);
        outtextxy(sWidth(50),sHeight(83),"Created and Saved Successfully !!");
        outtextxy(sWidth(50),sHeight(88),"Press [1] to View, Else Back");
        setcolor(RED);
        char choice=getch();
        if(choice=='1')
        {
            cleardevice();
            ifstream file(filepath);
            string lines;
            float line;
            float height=sHeight(25);
            outtextxy(sWidth(52),sHeight(9.5),"Job Application");
            while (file.good())
            {
                getline(file, lines);
                settextjustify(LEFT_TEXT,CENTER_TEXT);
                setcolor(BLACK);
                line=print_Lines(sWidth(2),height,lines);
                height+=line;
                delay(50);
                ignoreInput();
            }
            file.close();
        }
        else
            return ;
    }
    else if (ch=='0')
    {
        return ;
    }
    else
    {
        delay(100);
        ignoreInput();
        goto templete;
    }
}


void removeStringFromFile(const std::string& filename, const std::string& stringToRemove)
{
    // Open the file in input mode to read existing content
    std::ifstream infile(filename);

    // Read the content of the file into a vector of strings
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(infile, line))
    {
        if (line != stringToRemove)
        {
            lines.push_back(line);
        }
    }

    // Close the input file
    infile.close();

    // Open the file in output mode to write the modified content
    std::ofstream outfile(filename);

    // Write the modified content back to the file
    for (const auto& modifiedLine : lines)
    {
        outfile << modifiedLine << std::endl;
    }

    // Close the output file
    outfile.close();

}

void displayTagGenre(string type, string loggedInUser)
{
choice1:
    cleardevice();
    if (type == "Tags")
        outtextxy(sWidth(50), sHeight(5), "My Tags");
    if (type == "Genre")
        outtextxy(sWidth(50), sHeight(5), "Shared Lits");
    string folderPath = "C:\\User_Data\\" + loggedInUser + "\\" + type;
    string files[1000];
    DIR* dir;
    struct dirent* entry;
    dir = opendir(folderPath.c_str());
    int i = 0;
    while ((entry = readdir(dir)) != nullptr)
    {
        if (entry->d_type == DT_REG)
        {
            files[i] = entry->d_name;
            i++;
        }
    }
    closedir(dir);
    if (i != 0)
    {
        float height = sHeight(20);
        for (int j = 0; j < i; j++)
        {
            int temp = j + 1;
            char sN[100];
            sprintf(sN, "[%d]", temp);
            settextjustify(LEFT_TEXT, CENTER_TEXT);
            size_t dotPos = files[j].rfind('.'); // Removes .txt from the end
            string sharedFile = files[j].substr(0, dotPos);
            outtextxy(sWidth(40), height, sN);
            if (type == "Genre" || type == "Tags")
                outtextxy(sWidth(45), height, const_cast<char*>(sharedFile.c_str()));
            height += sHeight(5);
        }
    }
    else
    {
        settextjustify(CENTER_TEXT, CENTER_TEXT);
        outtextxy(sWidth(50), sHeight(50), "Nothing Created Yet !!");
    }
    //////////////////////////////////////////////////////////////////////////////////////

    char choice = getch();
    int fileNo = choice - '0';
    if (fileNo > 0 && fileNo <= i)
    {
        int selected = fileNo - 1;
        string fileName = "C:\\User_Data\\" + loggedInUser + "\\" + type + "\\" + files[selected];

        string lines, display, owner[100], viewer[100];
        float height = sHeight(20);
        cleardevice();

        // Open the file in input mode to read existing content
        int viewerCount = 1;
        ifstream infile(fileName);
        display = type + " :: " + files[selected];
        settextjustify(CENTER_TEXT, CENTER_TEXT);
        outtextxy(sWidth(50), sHeight(5), const_cast<char*>(display.c_str()));
        if (type == "Genre" || type == "Tags")
        {
            while (infile.good())
            {
                getline(infile, lines);
                string isDeleted = "C:\\User_Data\\" + loggedInUser + "\\Lits\\" + lines + ".txt";
                ifstream file(isDeleted);
                if (infile.is_open())
                {
                    settextjustify(LEFT_TEXT, CENTER_TEXT);
                    setcolor(BLACK);
                    if (!lines.empty())
                    {
                        outtextxy(sWidth(33), height, " - ");
                        outtextxy(sWidth(37), height, const_cast<char*>(lines.c_str()));
                        height += sHeight(3);
                        delay(50);
                        ignoreInput();
                    }
                }
                else
                {
                    removeStringFromFile(fileName, lines);
                }
                infile.close();
            }
            getch();
        }
        goto choice1;
    }
}

void removeFileIfEmpty(const std::string& filename)
{
    std::ifstream checkfile(filename);

    // Check if the file is empty
    if (checkfile.peek() == std::ifstream::traits_type::eof())
    {
        checkfile.close();
        remove(filename.c_str());
    }
    else
    {
        checkfile.close();
    }
}


void displayShared(string type, string loggedInUser)
{
choice1:
    setcolor(BLACK);
    cleardevice();
    if (type == "Shared")
        outtextxy(sWidth(50), sHeight(5), "Shared Lits");
    string folderPath = "C:\\User_Data\\" + loggedInUser + "\\" + type;
    string files[1000];
    DIR* dir;
    struct dirent* entry;
    dir = opendir(folderPath.c_str());
    int i = 0;
    while ((entry = readdir(dir)) != nullptr)
    {
        if (entry->d_type == DT_REG)
        {
            files[i] = entry->d_name;
            i++;
        }
    }
    closedir(dir);
    if (i != 0)
    {
        float height = sHeight(20);
        for (int j = 0; j < i; j++)
        {
            int temp = j + 1;
            char sN[100];
            sprintf(sN, "[%d]", temp);
            settextjustify(LEFT_TEXT, CENTER_TEXT);
            size_t dotPos = files[j].rfind('.'); // Removes .txt from the end
            string sharedFile = files[j].substr(0, dotPos);
            outtextxy(sWidth(40), height, sN);
            if (type == "Shared")
            {
                string owner, viewer;
                string fileName = "C:\\User_Data\\" + loggedInUser + "\\Shared\\" + sharedFile + ".txt";
                ifstream file(fileName);
                file >> viewer >> owner;
                file.close();
                string checkname = loggedInUser;
                string filename = owner;
                transform(checkname.begin(), checkname.end(), checkname.begin(), ::tolower);
                transform(filename.begin(), filename.end(), filename.begin(), ::tolower);
                if (checkname == filename)
                {
                    string displayStr = sharedFile + " [See Viewers]";
                    outtextxy(sWidth(45), height, const_cast<char*>(displayStr.c_str()));
                }
                else
                {
                    string displayStr = sharedFile + "[" + filename + "]";
                    outtextxy(sWidth(45), height, const_cast<char*>(displayStr.c_str()));
                }
            }
            height += sHeight(5);
        }
    }
    else
    {
        settextjustify(CENTER_TEXT, CENTER_TEXT);
        outtextxy(sWidth(50), sHeight(50), "No Files Shared Yet !!");
    }
    //////////////////////////////////////////////////////////////////////////////////////

    char choice = getch();
    int fileNo = choice - '0';
    if (fileNo > 0 && fileNo <= i)
    {
        int selected = fileNo - 1;
        string fileName = "C:\\User_Data\\" + loggedInUser + "\\" + type + "\\" + files[selected];

        setfillstyle(SOLID_FILL, backgroundColor);
        bar(sWidth(0), sHeight(90), sWidth(100), sHeight(100));

        string lines, display, owner[100], viewer[100];
        float lineNo, height = sHeight(20);
        cleardevice();

        // Open the file in input mode to read existing content
        int viewerCount = 1;
        ifstream infile(fileName);
        display = type + " :: " + files[selected];
        settextjustify(CENTER_TEXT, CENTER_TEXT);
        outtextxy(sWidth(50), sHeight(5), const_cast<char*>(display.c_str()));

        while(infile >> viewer[viewerCount] >> owner[viewerCount])
        {
            viewerCount++;
        }
        string checkname = loggedInUser;
        string filename = owner[fileNo];
        transform(checkname.begin(), checkname.end(), checkname.begin(), ::tolower);
        transform(filename.begin(), filename.end(), filename.begin(), ::tolower);
        if (filename == checkname)
        {
            for(int start=1; start<viewerCount; start++)
            {
                settextjustify(LEFT_TEXT,CENTER_TEXT);
                char sN[100];
                sprintf(sN, "[%d]", start);
                string No = sN;
                string display = No + "  " + viewer[start];
                outtextxy(sWidth(40), height, const_cast<char*>(display.c_str()));
                height += sHeight(3);
                delay(50);
                ignoreInput();
            }
            char option = getch();
            int i = option - '0';
            if (i > 0 && i <=viewerCount)
            {
                string fileNameforViewer = "C:\\User_Data\\" + viewer[i] + "\\Shared\\" + files[selected];
                string fileNameforOwner = "C:\\User_Data\\" + loggedInUser + "\\Shared\\" + files[selected];
                string findinOwner = viewer[i] + " " + owner[i];
                line(sWidth(0), sHeight(92), sWidth(100), sHeight(92));
                settextjustify(CENTER_TEXT, CENTER_TEXT);
                outtextxy(sWidth(50), sHeight(95), "Remove Access for this User ?[y/Y]");
                char what = getch();
                if (what == 'y' || what == 'Y')
                {
                    remove(fileNameforViewer.c_str());
                    removeStringFromFile(fileNameforOwner, findinOwner);
                    removeFileIfEmpty(fileNameforOwner);
                    setcolor(GREEN);
                    outtextxy(sWidth(50), sHeight(98), "Access Removed");
                    getch();
                    outtextxy(sWidth(50), sHeight(98), const_cast<char*>(fileNameforOwner.c_str()));
                    getch();
                    setcolor(BLACK);
                }
            }
            else
            {
                goto choice1;
            }
        }
        else
        {
            string displayFile = "C:\\User_Data\\" + owner[selected+1] + "\\Lits\\" + files[selected];
            string lines;
            float lineNo, height = sHeight(20);

            // Open the file in input mode to read existing content
            ifstream outfile(displayFile);
            if(outfile.is_open())
            {
                setcolor(BLACK);
                settextjustify(CENTER_TEXT,CENTER_TEXT);
                outtextxy(sWidth(50),sHeight(92),"Write any comments ?![y/Y]");
                line(sWidth(0),sHeight(90),sWidth(100),sHeight(90));
                while (outfile.good())
                {
                    getline(outfile, lines);
                    settextjustify(LEFT_TEXT, CENTER_TEXT);
                    setcolor(BLACK);
                    lineNo = print_Lines(sWidth(3), height, lines);
                    height += lineNo;
                    delay(10);
                    ignoreInput();
                }
                char sentMsg=getch();
                if(sentMsg=='y'||sentMsg=='Y')
                {
                    string Message=userInput(sWidth(40),sHeight(95));
                    string msgFile="C:\\User_Data\\"+owner[selected+1]+"\\messages.txt";
                    ofstream msg(msgFile,ios::in|ios::app);
                    msg<<loggedInUser<<" Commented: (On File "<<files[selected]<<") "<<Message<<endl;
                    setcolor(GREEN);
                    settextjustify(CENTER_TEXT,CENTER_TEXT);
                    outtextxy(sWidth(50),sHeight(98),"Comment Sent !");
                    msg.close();
                    setcolor(BLACK);
                }
            }
            else
            {
                outtextxy(sWidth(50),sHeight(50),"Error");
            }

            infile.close();
            outfile.close();

        }
        getch();
        goto choice1;
    }
}

void newSection::createLit()
{
CREATE:
    readimagefile("C:\\User_Data\\asset\\lits.jpg",sWidth(35),sHeight(5),sWidth(39),sHeight(10));
    settextstyle(1,0,5);
    setbkcolor(backgroundColor);
    setcolor(BLACK);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    outtextxy(sWidth(52),sHeight(9.5),"Literatures");
    settextstyle(0,0,2);
    readimagefile("C:\\User_Data\\asset\\my lits.jpg",startxDisplay,startyDisplay,startxDisplay+imageWidth,startyDisplay+imageHeight);
    outtextxy((startxDisplay+startxDisplay+imageWidth)/2,startyDisplay+imageHeight+padding/2,"My Lits");

    readimagefile("C:\\User_Data\\asset\\newLit.jpg",startxDisplay+imageWidth+padding,startyDisplay,startxDisplay+2*imageWidth+padding,startyDisplay+imageHeight);
    outtextxy((2*startxDisplay+3*imageWidth+2*padding)/2,startyDisplay+imageHeight+padding/2,"Create New");

    readimagefile("C:\\User_Data\\asset\\sharedlits.jpg",startxDisplay+2*imageWidth+2*padding,startyDisplay,startxDisplay+3*imageWidth+2*padding,startyDisplay+imageHeight);
    outtextxy((2*startxDisplay+5*imageWidth+4*padding)/2,startyDisplay+imageHeight+padding/2,"Shared");
CHOICE:
    char choice=getch();
    if (choice=='1')
    {
choice1:
        cleardevice();
        setcolor(BLACK);
        outtextxy(sWidth(50),sHeight(5),"Saved Lits");
        string folderPath = "C:\\User_Data\\"+loggedInUser+"\\Lits";
        string files[1000];
        DIR* dir;
        struct dirent* entry;
        dir = opendir(folderPath.c_str());
        int i=0;
        while ((entry = readdir(dir)) != nullptr)
        {
            if (entry->d_type == DT_REG)
            {
                files[i]=entry->d_name;
                i++;
            }
        }
        closedir(dir);
        if(i!=0)
        {
            float height=sHeight(20);
            for(int j=0; j< i; j++)
            {
                int temp=j+1;
                char sN[100];
                sprintf(sN,"[%d]",temp);
                settextjustify(LEFT_TEXT,CENTER_TEXT);
                outtextxy(sWidth(40),height,sN);
                outtextxy(sWidth(45),height,const_cast<char*>(files[j].c_str()));
                height+=sHeight(5);
            }
            settextjustify(CENTER_TEXT,CENTER_TEXT);
        }
        else
        {
            outtextxy(sWidth(50),sHeight(50),"No any saved Files");
        }
        char choice=getch();
        int fileNo=choice-'0';
        if(fileNo>0&&fileNo<=i)
        {
            int selected=fileNo-1;
            string fileName="C:\\User_Data\\"+loggedInUser+"\\Lits\\"+files[selected];
            line(sWidth(0),sHeight(90),sWidth(100),sHeight(90));
            settextjustify(LEFT_TEXT,CENTER_TEXT);
            outtextxy(sWidth(30),sHeight(93),"FileName: ");
            outtextxy(sWidth(40),sHeight(93),const_cast<char*>(fileName.c_str()));
            outtextxy(sWidth(15),sHeight(97),"[1] Delete ");
            outtextxy(sWidth(35),sHeight(97),"[2] Open ");
            outtextxy(sWidth(55),sHeight(97),"[3] Edit ");
            outtextxy(sWidth(75),sHeight(97),"[4] Share ");
            char subChoice=getch();
            setfillstyle(SOLID_FILL,backgroundColor);
            bar(sWidth(0),sHeight(90),sWidth(100),sHeight(100));
            switch(subChoice)
            {
            case '1':                       //remove file
            {
                remove(fileName.c_str());
                settextjustify(CENTER_TEXT,CENTER_TEXT);
                outtextxy(sWidth(50),sHeight(95),"File Deleted !!");
                getch();
                goto choice1;
            }
            case '2':                       // Open file in append mode;
            {
                string lines;
                float line, height = sHeight(5);

                cleardevice();

                // Open the file in input mode to read existing content
                ifstream infile(fileName);

                while (infile.good())
                {
                    getline(infile, lines);
                    settextjustify(LEFT_TEXT, CENTER_TEXT);
                    setcolor(BLACK);
                    line = print_Lines(sWidth(3), height, lines);
                    height += line;
                    delay(50);
                    ignoreInput();
                }

                infile.close();  // Close the file before reopening in output mode

                // Open the file in output mode to append new content
                ofstream outfile(fileName, ios::app);

                string Content = WriteInConsole(20, height, "");

                outfile << Content;

                settextjustify(CENTER_TEXT, CENTER_TEXT);
                setcolor(GREEN);
                outtextxy(sWidth(50), sHeight(83), " Saved Successfully !!");
                getch();
                setcolor(RED);
                outfile.close();
                goto choice1;
            }
            case '3':                       //Edit File ....
            {
                cleardevice();
                ifstream infile(fileName);
                string lines;
                float lineH, height=sHeight(5);
                while (infile.good())
                {
                    getline(infile, lines);
                    settextjustify(LEFT_TEXT, CENTER_TEXT);
                    setcolor(BLACK);
                    lineH = print_Lines(sWidth(3), height, lines);
                    height += lineH;
                    delay(50);
                    ignoreInput();
                }
                line(sWidth(0),sHeight(90),sWidth(100),sHeight(90));
                settextjustify(LEFT_TEXT,CENTER_TEXT);
                outtextxy(sWidth(30),sHeight(93),"Find: ");
                string findStr=userInput(sWidth(50),sHeight(93));
                outtextxy(sWidth(30),sHeight(96),"Replace: ");
                string replaceStr=userInput(sWidth(50),sHeight(96));
                editString(fileName,findStr,replaceStr);
                setcolor(GREEN);
                outtextxy(sWidth(50), sHeight(98), " Saved Successfully !!");
                getch();
                setcolor(RED);
                goto choice1;
            }
            case '4':
            {
                settextjustify(LEFT_TEXT,CENTER_TEXT);
                outtextxy(sWidth(30),sHeight(95),"UserName: ");
                string sharedUser=userInput(sWidth(55),sHeight(95));
                string userExists="C:\\User_Data\\"+sharedUser;
                DIR* dir1;
                dir1=opendir(userExists.c_str());
                if(dir1&&sharedUser!=loggedInUser)
                {
                    string directory="C:\\User_Data\\"+loggedInUser+"\\Shared\\"+files[selected];
                    ofstream file;
                    file.open(directory,ios::app);
                    file<<sharedUser<<" "<<loggedInUser<<endl;
                    file.close();
                    string directory1="C:\\User_Data\\"+sharedUser+"\\Shared\\"+files[selected];
                    ofstream file1;
                    file1.open(directory1,ios::app);

                    file1<<sharedUser<<" "<<loggedInUser<<endl;
                    file1.close();
                    string file2Name="C:\\User_Data\\"+sharedUser+"\\messages.txt";
                    ofstream file2;
                    file2.open(file2Name,ios::in|ios::app);
                    file2<<"'"<<loggedInUser<<"'"<<" shared a file with you"<<endl;
                    file2.close();
                    settextjustify(CENTER_TEXT,CENTER_TEXT);
                    setcolor(GREEN);
                    outtextxy(sWidth(50),sHeight(97),"Shared Successfully");
                    getch();
                    setcolor(BLACK);
                }
                else
                {
                    setfillstyle(SOLID_FILL,backgroundColor);
                    bar(sWidth(0),sHeight(90),sWidth(100),sHeight(100));
                    outtextxy(sWidth(50),sHeight(95),"User does not exists !");
                    getch();
                    goto choice1;
                }
            }
            default:
            {
                goto choice1;
            }
            }
        }
        cleardevice();
        goto CREATE;
    }
    else if(choice=='2')
    {
        cleardevice();
        outtextxy(sWidth(30),sHeight(5),"TITLE: ");
        string title=userInput(sWidth(60),sHeight(5));
        outtextxy(sWidth(5),sHeight(10),"Tags: ");
        string tagInput=userInput(sWidth(20),sHeight(10));
        outtextxy(sWidth(50),sHeight(10),"Genres: ");
        string genreInput=userInput(sWidth(70),sHeight(10));

        // Using stringstream to split tags by commas
        std::stringstream ss(tagInput);
        std::string tag;
        std::vector<std::string> tags;
        while (std::getline(ss, tag, ','))
        {
            // Trim leading and trailing whitespaces
            tag.erase(0, tag.find_first_not_of(" \t\n\r\f\v"));
            tag.erase(tag.find_last_not_of(" \t\n\r\f\v") + 1);
            string filePath="C:\\User_Data\\"+loggedInUser+"\\tags\\"+tag+".txt";
            ofstream file;
            file.open(filePath,ios::app);
            file<<title<<endl;
            file.close();
            tags.push_back(tag);
        }

        // Using stringstream to split genre by commas
        std::stringstream sss(genreInput);
        std::string genre;
        std::vector<std::string> genres;
        while (std::getline(sss, genre, ','))
        {
            // Trim leading and trailing whitespaces
            genre.erase(0, genre.find_first_not_of(" \t\n\r\f\v"));
            genre.erase(genre.find_last_not_of(" \t\n\r\f\v") + 1);
            string filePath="C:\\User_Data\\"+loggedInUser+"\\genre\\"+genre+".txt";
            ofstream file;
            file.open(filePath,ios::app);
            file<<title<<endl;
            file.close();
            genres.push_back(genre);
        }
        string Content=WriteInConsole(3,sHeight(20),"");

        string fileName="C:/User_Data/"+loggedInUser+"/Lits/"+title+".txt";
        ofstream file(fileName);
        if(file.is_open())
        {
            file<<"Tags:   "<<tagInput<<endl;
            file<<"Genres: "<<genreInput<<endl;
            file<<"Title:  "<<title<<endl<<endl<<endl;
            file<<Content<<endl;
            file.close();
            settextjustify(CENTER_TEXT,CENTER_TEXT);
            setcolor(GREEN);
            outtextxy(sWidth(50),sHeight(83),"Saved Successfully !!");
            setcolor(RED);
        }
        else
            outtextxy(100,200,"Error");

        getch();
        cleardevice();
        goto CREATE;
    }
    else if(choice=='3')
    {
        cleardevice();
        displayShared("Shared",loggedInUser);
//        getch();
        cleardevice();
        goto CREATE;
    }
    else if(choice=='0')
    {
        cleardevice();
        return;
    }
    else
    {
        delay(100);
        ignoreInput();
        goto CHOICE;
    }
}




void newSection::leafModule()
{
LeafSection:
    cleardevice();
    setfillstyle(SOLID_FILL,backgroundColor);
    floodfill(0,0,backgroundColor);

    displaySection();
CHOICE:
    char choice=getch();
    switch(choice)
    {
    case '1':
    {
        cleardevice();
        writeNotes();
        cleardevice();
        goto LeafSection;
    }
    case '2':
    {
        cleardevice();
        createTemplate();
        cleardevice();
        goto LeafSection;
    }
    case '3':
    {
        cleardevice();
        createLit();
        cleardevice();
        goto LeafSection;
    }
    case '4':
    {
        cleardevice();
        displayTagGenre("Tags",loggedInUser);
        cleardevice();
        goto LeafSection;
    }
    case '5':
    {
        cleardevice();
        displayTagGenre("Genre",loggedInUser);
        cleardevice();
        goto LeafSection;
    }
    case '0':
    {
        return;
    }
    default:
    {
        delay(100);
        ignoreInput();
        goto CHOICE;
    }
    }
}

/*************************************************************************************************************************
----------------------------------LEAF MODULE (NOTES-LITS) ENDED--------------------------------------------------------------
**************************************************************************************************************************
------------------------------------- BEGINS------------------------------------------------------
*************************************************************************************************************************/


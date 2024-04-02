#define maxKey 32           //Max size of leafHandle and Passkey
#define minHandle 3
#define minKey 8

int backgroundColor=RGB(174, 214, 223);
int textBar=RGB(48, 147, 189);    //FOr the Asking
int inputBar=RGB(200, 179, 238);      //For user input

float sWidth(float percentage)
{
    float maxWidth=getmaxwidth();
    float width = (maxWidth / 100) * percentage;
    return width;
}

void ignoreInput()
{
    while (kbhit())
    {
        getch();
    }
}

float sHeight(float percentage)
{
    float maxWidth=getmaxheight();
    float width = (maxWidth / 100) * percentage;
    return width;
}

void roundBar(float left,float top, float right, float buttom,float radius)
{
//float radius;
    bar(left,top,right,buttom);
    bar(left,top-radius,right,top); //top
    bar(left-radius,top,left,buttom); // left
    bar(left,buttom,right,buttom+radius); //buttom
    bar(right,buttom,right+radius,top); //right
    pieslice(left,top,90,180,radius); //top left
    pieslice(left,buttom,180,270,radius); //buttom left
    pieslice(right,buttom,270,0,radius); //buttom right
    pieslice(right,top,0,90,radius); //top right
}


float print_Lines(float width,float height,std::string line)
{
    float textHeight=0;
    if (textwidth(const_cast<char*>(line.c_str())) >= sWidth(95))
    {
        std::string printLines[1000];
        int i = 0;

        for (char &c : line)
        {
            printLines[i] += c;

            if (textwidth(const_cast<char*>(printLines[i].c_str())) >= sWidth(95))
            {
                i++;
            }
        }

        // Display the sub-lines
        for (int j = 0; j <= i; j++)
        {
            outtextxy(width, height + textHeight, const_cast<char*>(printLines[j].c_str()));
            textHeight+=textheight(const_cast<char*>(line.c_str()));
        }
    }
    else
    {
        // Display the line as is if it fits within screen width
        outtextxy(width, height, const_cast<char*>(line.c_str()));
        textHeight+=textheight(const_cast<char*>(line.c_str()));
    }
    return textHeight;
}

void scrollingConsole(std::string fileName,float startX, float startY, float endX,float endY)
{
    setbkcolor(backgroundColor);
    // Open the file for reading
    std::ifstream file(fileName);
    float currY = startY;      // Current y-coordinate
    std::vector<std::string> lines; // Store lines from the file

    std::string line;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }

    file.close(); // Close the file

    int currentLine = 0; // Track the current line to display
    settextstyle(0,0,0);
    settextjustify(LEFT_TEXT,CENTER_TEXT);
    // Display the lines using print_Lines
TOP:
    setfillstyle(SOLID_FILL,backgroundColor);
    bar(startX-sWidth(0.5),startY-sWidth(0.5),endX+sWidth(0.5),endY);
    while (1)
    {
        float textHeight = startY;

        for (int i = currentLine; i < lines.size(); i++)
        {
            textHeight += print_Lines(startX, textHeight, lines[i]);

            // If we reach the end of the screen, stop displaying
            if (textHeight >= endY-sWidth(1))
            {
                break;
            }
        }
        // Check for keypress to scroll up or down
        char key = getch();

        if (key == 72)   // Up arrow key
        {
            if (currentLine > 0)
            {
                currentLine-=3;
                delay(100);
                ignoreInput();
                goto TOP;
            }
            else
            {
                delay(100);
                ignoreInput();
                goto TOP;
            }
        }
        else if (key == 80)     // Down arrow key
        {
            if (currentLine < lines.size() - 10)
            {
                currentLine+=3;
                delay(100);
                ignoreInput();
                goto TOP;
            }
            else
            {
                delay(100);
                ignoreInput();
                goto TOP;
            }
        }
        else
            break;
    }
}

std::string getUserInput(float x_coordinate, float y_coordinate)
{
    std::string userInput;
    char ch;

    while (true)
    {
        ch = getch();

        if (ch == 13) // Enter key
            break;

        if (ch == 8) // Backspace
        {
            if (!userInput.empty())
            {
                userInput.pop_back();
                // Clear the previous character on the screen
                outtextxy(x_coordinate, y_coordinate, "                                 ");
                outtextxy(x_coordinate, y_coordinate, const_cast<char*>(userInput.c_str()));
            }
        }
        else if((isalnum(ch) || ispunct(ch)||ch==' ')&&userInput.length()<32)
        {
            userInput += ch;
            outtextxy(x_coordinate, y_coordinate, const_cast<char *>(userInput.c_str()));
        }
        else
        {
            ignoreInput();
        }
    }

    return userInput;
}

//TO check the password validation:
bool validation(std::string str, float y_coordinate)
{
    y_coordinate=(y_coordinate/sHeight(100))*100;
    bool upper=false;
    bool lower=false;
    bool special=false;
    bool num=false;
    for(char ch: str)
    {
        if(islower(ch))
            lower=true;
        else if(isupper(ch))
            upper=true;
        else if(isdigit(ch))
            num=true;
        else if(ispunct(ch))
            special=true;
    }
    if(num)
    {
        readimagefile("C:\\User_Data\\asset\\passok.jpg",sWidth(60.3),sHeight(y_coordinate+2),sWidth(61.8),sHeight(y_coordinate+3.5));
    }
    else
    {
        setfillstyle(SOLID_FILL,backgroundColor);
        bar(sWidth(60.2),sHeight(y_coordinate+1.9),sWidth(61.9),sHeight(y_coordinate+3.6));
    }
    if(special)
    {
        readimagefile("C:\\User_Data\\asset\\passok.jpg",sWidth(70.3),sHeight(y_coordinate+2),sWidth(71.8),sHeight(y_coordinate+3.5));
    }
    else
    {
        setfillstyle(SOLID_FILL,backgroundColor);
        bar(sWidth(70.2),sHeight(y_coordinate+1.9),sWidth(71.9),sHeight(y_coordinate+3.6));
    }
    if(lower)
    {
        readimagefile("C:\\User_Data\\asset\\passok.jpg",sWidth(52),sHeight(y_coordinate+2),sWidth(53.5),sHeight(y_coordinate+3.5));
    }
    else
    {
        setfillstyle(SOLID_FILL,backgroundColor);
        bar(sWidth(51.9),sHeight(y_coordinate+1.9),sWidth(53.6),sHeight(y_coordinate+3.6));
    }
    if(upper)
    {
        readimagefile("C:\\User_Data\\asset\\passok.jpg",sWidth(43.5),sHeight(y_coordinate+2),sWidth(45),sHeight(y_coordinate+3.5));
    }
    else
    {
        setfillstyle(SOLID_FILL,backgroundColor);
        bar(sWidth(43.4),sHeight(y_coordinate+1.9),sWidth(45.1),sHeight(y_coordinate+3.6));
    }
    if(num && special && lower && upper)
        return true;
    else
        return false;
}

void displayPassValid(float height)
{
    height=(height/sHeight(100))*100;
    float y_coordinate=(height+3.5);

//    float y_coordinate=49.5;
    setcolor(RED);
    setbkcolor(inputBar);
    settextstyle(2,0,0);
    settextjustify(LEFT_TEXT,CENTER_TEXT);
    setbkcolor(backgroundColor);
    outtextxy(sWidth(40),sHeight(y_coordinate),"UpperCase");
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    outtextxy(sWidth(50),sHeight(y_coordinate),"LowerCase");
    settextjustify(RIGHT_TEXT,CENTER_TEXT);
    outtextxy(sWidth(60),sHeight(y_coordinate),"Digit");
    outtextxy(sWidth(70),sHeight(y_coordinate),"Special Character");

    //To remove passValidation:
//    setfillstyle(SOLID_FILL,backgroundColor);
//    bar(sWidth(40),sHeight(55),sWidth(72),sHeight(57));  //54-58
}

std::string getpassword(float x_coordinate, float y_coordinate, bool ispassword)
{
getAgain:
    std::string userInput;
    std::string astrik;
    std::string print = "#SECURED";
    int i = 0;
    int j = 0;
    bool showpassword = false;
//    bool gotoSignup = false;
    bool isValidated= false;
    delay(500);
    if(ispassword)
        displayPassValid(y_coordinate);

    settextjustify(CENTER_TEXT,CENTER_TEXT);
    setbkcolor(inputBar);
    settextstyle(0,0,0);
    while (true)
    {
        char ch = getch();

        if (ch == 13)  // Enter key
        {
            outtextxy(x_coordinate,y_coordinate,"                                         ");
            outtextxy(x_coordinate,y_coordinate,const_cast<char*>(astrik.c_str()));
            if(ispassword)
            {
                setfillstyle(SOLID_FILL,backgroundColor);
                bar(sWidth(40),sHeight((y_coordinate/sHeight(100))*100+2),sWidth(72),sHeight((y_coordinate/sHeight(100))*100+4));  //Remove PassValidation
            }
            break;
        }
        if (ch == 8)   // Backspace
        {
            if (i >0)
            {
                i--;
                userInput.pop_back();
                astrik.pop_back();
            }
            if(i<0)
                i=0;
            if(showpassword)
            {
                outtextxy(x_coordinate,y_coordinate,"                                         ");
                outtextxy(x_coordinate,y_coordinate,const_cast<char*>(userInput.c_str()));
            }
            else
            {
                outtextxy(x_coordinate,y_coordinate,"                                         ");
                outtextxy(x_coordinate,y_coordinate,const_cast<char*>(astrik.c_str()));
            }
        }
        else if (isalnum(ch) || ispunct(ch))
        {
            if (i < maxKey)
            {
                userInput += ch;
                j = i % 8;
                astrik += print[j];
                if (!showpassword)
                {
                    outtextxy(x_coordinate, y_coordinate, const_cast<char*>(astrik.c_str()));
                }
                else
                {
                    outtextxy(x_coordinate, y_coordinate, const_cast<char*>(userInput.c_str()));
                }
                i++;
            }
        }
        else if (ch == 19 && (GetAsyncKeyState(VK_CONTROL)))
        {
            showpassword = true;
            outtextxy(x_coordinate,y_coordinate,"                                         ");
            outtextxy(x_coordinate, y_coordinate, const_cast<char*>(userInput.c_str()));
        }
        else if (ch == ' ')
        {
            showpassword = false;
            outtextxy(x_coordinate,y_coordinate,"                                         ");
            outtextxy(x_coordinate, y_coordinate, const_cast<char*>(astrik.c_str()));
        }
        if(ispassword)
             isValidated=validation(userInput,y_coordinate);
    }

    if((userInput.length())<minKey)
    {
        outtextxy(x_coordinate,y_coordinate,"                                         ");
        readimagefile("C:\\User_Data\\asset\\warning.jpg",sWidth(68),y_coordinate-15,sWidth(70),y_coordinate+10);
        setcolor(RED);
        outtextxy(x_coordinate,y_coordinate,"Minimum 8 characters !!");
        delay(500);
        ignoreInput();
        getch();
        setcolor(inputBar);
        outtextxy(x_coordinate,y_coordinate,"                                         ");
        setfillstyle(SOLID_FILL,inputBar);
        bar(sWidth(68),y_coordinate-15,sWidth(70),y_coordinate+10);
        setcolor(RED);
        goto getAgain;
    }
    if(ispassword)
    {
        if(isValidated)
        {
            readimagefile("C:\\User_Data\\asset\\verified.jpg",sWidth(68),y_coordinate-15,sWidth(70),y_coordinate+10);
            return userInput;
        }
        else
        {
            settextstyle(11,0,1);
            readimagefile("C:\\User_Data\\asset\\warning.jpg",sWidth(68),y_coordinate-15,sWidth(70),y_coordinate+10);
            outtextxy(x_coordinate,y_coordinate,"Must have Upper, Lower, Number and Special Case");
            settextstyle(0,0,0);
            delay(500);
            ignoreInput();
            getch();
            setcolor(inputBar);
            outtextxy(x_coordinate,y_coordinate,"                                         ");
            setfillstyle(SOLID_FILL,inputBar);
            bar(sWidth(68),y_coordinate-15,sWidth(70),y_coordinate+10);
            setcolor(RED);
            goto getAgain;
        }
    }
    if(userInput.length()>minKey&&!ispassword)
        return userInput;
}



std::string userInput(float x_coordinate, float y_coordinate)
{
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(0,0,0);
    std::string inputString;
    std::string displayString;
    while(true)
    {
        char ch=getch();
        if(ch==13)
            break;

        if(isalnum(ch)||ispunct(ch)||ch==' ')
            inputString+=ch;
        if(ch==8)
        {
            if(!inputString.empty())
                inputString.pop_back();
        }
        if (inputString.length() > 30)
        {
            displayString = inputString.substr(inputString.length() - 30);
        }
        else
            displayString=inputString;
        outtextxy(x_coordinate,y_coordinate,"                                         ");
        outtextxy(x_coordinate,y_coordinate,const_cast<char*>(displayString.c_str()));
    }
    return inputString;
}

//Select the Image using windows API OpenFileLocation
std::string profileLocation()
{
    OPENFILENAME ofn;
    char profileLoc[MAX_PATH] = "";

    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.lpstrFile = profileLoc;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(profileLoc);
    ofn.lpstrFilter = "Image Files\0*.jpg\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;

    if (GetOpenFileName(&ofn))
    {
        return profileLoc;
    }
    // If no file was selected, return an empty string
    return "";
}


std::string resetCode(float x_coordinate, float y_coordinate)
{
    setcolor(RED);
    setbkcolor(inputBar);
    std::string resetStr, displayStr;
    bool show=false;
    int i=0;
    while(i<4)
    {
        char ch=getch();
        if(isdigit(ch))
        {
            resetStr+=ch;
            displayStr+='*';
            i++;
        }
        else if (ch==8 && !resetStr.empty())
        {
            resetStr.pop_back();
            displayStr.pop_back();
            outtextxy(x_coordinate,y_coordinate,"                                         ");
            outtextxy(x_coordinate,y_coordinate,const_cast<char*>(resetStr.c_str()));
            i--;
        }
        else if (ch == 19 && (GetAsyncKeyState(VK_CONTROL)))
            show=true;
        else if(ch==' ')
            show=false;
        else
            ignoreInput();
        if(show){
            outtextxy(x_coordinate,y_coordinate,"                                         ");
            outtextxy(x_coordinate,y_coordinate,const_cast<char*>(resetStr.c_str()));
        }
        else{
            outtextxy(x_coordinate,y_coordinate,"                                         ");
            outtextxy(x_coordinate,y_coordinate,const_cast<char*>(displayStr.c_str()));
        }
    }
    outtextxy(x_coordinate,y_coordinate,"                                         ");
    outtextxy(x_coordinate,y_coordinate,const_cast<char*>(displayStr.c_str()));
    return resetStr;
}


void copyImage(const std::string& inputPath, const std::string& finalPath)
{
    std::ifstream inputFile(inputPath, std::ios::binary);
    std::ofstream finalFile(finalPath, std::ios::binary);
    // Read and write the file content
    finalFile << inputFile.rdbuf();

    // Close the files
    inputFile.close();
    finalFile.close();
}

//This Function Block reads the contents from the file and store in string fileContents. It finds the string to be replaced and gets its position and then replace it by the new string.
void editString(const std::string& fileName, const std::string& oldPassword, const std::string& newPassword) {
    std::ifstream file(fileName);

    std::string fileContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    size_t pos = fileContents.find(oldPassword);

        fileContents.replace(pos, oldPassword.size(), newPassword);

        std::ofstream outfile(fileName);

        outfile << fileContents;
        outfile.close();
}




void displayLastNLines(const std::string& fileName, int n, float height)
{
    std::ifstream file(fileName);
//    int height=sHeight(30);
    std::vector<std::string> lines;
    std::string line;

    // Read all lines from the file
    while (std::getline(file, line))
    {
        lines.push_back(line);

    }

    // Determine the starting index for the last N lines
    int startIdx = std::max(0, static_cast<int>(lines.size()) - n);
    float final_height;
    // Display the last N lines
    for (int i = startIdx; i<lines.size(); i++)
    {
        std::string readline=lines[i];
        final_height=print_Lines(sWidth(3),height,readline);
        height+=final_height;
    }

    file.close();
}



bool isDateValid(const std::string& date) {
    // Define the date format (YYYY-MM-DD)
    std::regex dateRegex(R"(\b\d{4}-\d{2}-\d{2}\b)");

    // Check if the date matches the format
    if (!std::regex_match(date, dateRegex)) {
        return false;
    }

    // Parse the date components
    int year, month, day;
    sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day);

    // Check if the components form a valid date
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    // Additional checks for months with fewer than 31 days
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }

    // Check for February and leap years
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            return day <= 29;
        } else {
            return day <= 28;
        }
    }

    return true;
}


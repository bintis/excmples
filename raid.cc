std::chrono::Timer clock;


void Raid_Go_Code_Page ()
{
    ioMani.move_to(40, 90);
    ioMani.Left_click();
    Sleep(500);
    gpuMatchandClick(method, retry_15, Part_Input_ID, srcImage);
    //TO confire is botton exsist
    for (int ct1; ct1 <= 5;ct1++)
    {
        if (gpuMatchandClick(method, retry_15, Botton_Join, srcImage,100,0.9,false))
        {
            break;
        }
        else
        {
            Sleep(200);
            gpuMatchandClick(method, retry_15, Part_Input_ID, srcImage);
        }        
} 

void Raid_Get_Code()
{
    //Get new code
    ioMani.move_to(1172,750);
    Sleep(500);

    ioMani.move_to(691, 275);
    ioMani.Left_click();
    ioMani.Left_click();
    //! Get new code
}


auto Raid_Enter_And_Confirm()
{
    //Try press ok
    gpuMatchandClick(method, retry_15, Botton_Join, srcImage,100,0.9,true,-100,0,-100,0);
    Sleep(300);
    Press_key_set();
    Sleep(300);
    gpuMatchandClick(method, retry_15, Botton_Join, srcImage);
    Sleep(300);
    if (gpuMatchandClick(method, retry_15, Raid_Sel_sommon, srcImage,100,0.9,false))    //TO fix
    {
        std::cout << getTimeStamp() << "  [Raid]      Now at summon chk page .\n";
            /*Cod to chk hp*/
            if (){

            }else
            {
                goto TryEntry;
            }
            
        
    }else if (gpuMatchandClick(method, retry_15, Raid_End, srcImage,100,0.9,false))  //TO fix
    {
        std::cout << getTimeStamp() << "  [Raid]      Raid already ended .\n";
        goto TryEntry;
    }else if (gpuMatchandClick(method, retry_15,Check Pending, srcImage,100,0.9,false))  //TO fix
    {
        std::cout << getTimeStamp() << "  [Raid]      Check pending  .\n";
        /*Here code to check pending*/
    }else if (gpuMatchandClick(method, retry_15, Raid_Full, srcImage,100,0.9,false))  //TO fix
    {
        std::cout << getTimeStamp() << "  [Raid]      Room is full .\n";
        goto TryEntry;
    }
    
}


auto Raid_Finalize(int wait = 180)
{

    auto start = std::chrono::system_clock::now();      // 計測スタート時刻を保存
    auto end = std::chrono::system_clock::now();       // 計測終了時刻を保存
    auto dur = end - start;       
    auto sec = std::chrono::duration_cast<std::chrono::seconds>(dur).count();


    while (sec != wait) //180seconds
    {
        Sleep (500);
        if(gpuMatchandClick(method, retry_15,Raid End, srcImage,100,0.9,false))// tofix
        {
            std::cout << getTimeStamp() << "  [Raid]      Raid was ended.\n";
            goto Finalize;
        }
        if (gpuMatchandClick(method, retry_less, Part_questresult, srcImage, 1000, 0.97, false))
        {
            std::cout << getTimeStamp() << "  [Raid]      Now in Loot page.\n";
            goto Finalize;
        }
        
        //Refresh time stamp
        end = std::chrono::system_clock::now();
        dur = end - start; 
        sec = std::chrono::duration_cast<std::chrono::seconds>(dur).count();
        //std::cout << sec << " sec \n";

    }
    

Finalize:
std::cout << getTimeStamp() << "  [Raid]      Time is up ,Go next round.\n";


}
 
 
 else if (set["Mode"] == "Raid")
    {
        Sleep(2000);
        std::cout << getTimeStamp() << "  [Raid]      Start Raid mode for " << set["Loop"] << " times.\n";
        //std::thread t1(Manipulator);
        for (int ct = 1; ct <= count; ct++)
        {
            std::cout << getTimeStamp() << "  [Raid]      Raid for the " << ct << " time.\n";
            goto TryEntry;

            TryEntry:
            {
                Raid_Go_Code_Page();
                Raid_Get_Code();
            }

            Raid_Enter_And_Confirm();
            Battle_Select_Summon(set);
            Sleep(500);
            Battle_init(EnableFA, EnableQuickSummon,EnableBlackScreenFA,WaitForLoading);
            Raid_Finalize();
        }
        return 0;
    }

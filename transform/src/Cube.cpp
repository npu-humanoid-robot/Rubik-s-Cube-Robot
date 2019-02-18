#include <Cube.h>

void cube::clear()
{
    for (int i = 0; i < 9; i++)
    {
        topset[i] = 'U';
        froset[i] = 'F';
        rigset[i] = 'R';
        lefset[i] = 'L';
        botset[i] = 'D';
        behset[i] = 'B';
    }
}

void cube::output()
{
    //UF UR UB UL DF DR DB DL FR FL BR BL UFR URB UBL ULF DRF DFL DLB DBR
    char message[50];
    for (int i = 0; i < 48; i++)
    {
        message[i] = ' ';
    }
    message[0] = topset[7];
    message[1] = froset[1]; //UF

    message[2] = topset[5];
    message[3] = rigset[1]; //UR

    message[4] = topset[1];
    message[5] = behset[1]; //UB

    message[6] = topset[3];
    message[7] = lefset[1]; //UL

    message[8] = botset[1];
    message[9] = froset[7]; //DF

    message[10] = botset[5];
    message[11] = rigset[7]; //DR

    message[12] = botset[7];
    message[13] = behset[7]; //DB

    message[14] = botset[3];
    message[15] = lefset[7]; //DL

    message[16] = froset[5];
    message[17] = rigset[3]; //FR

    message[18] = froset[3];
    message[19] = lefset[5]; //FL

    message[20] = behset[3];
    message[21] = rigset[5]; //BR

    message[22] = behset[5];
    message[23] = lefset[3]; //BL

    message[24] = topset[8];
    message[25] = froset[2];
    message[26] = rigset[0]; //UFR

    message[27] = topset[2];
    message[28] = rigset[2];
    message[29] = behset[0]; //URB

    message[30] = topset[0];
    message[31] = behset[2];
    message[32] = lefset[0]; //UBL

    message[33] = topset[6];
    message[34] = lefset[2];
    message[35] = froset[0]; //ULF

    message[36] = botset[2];
    message[37] = rigset[6];
    message[38] = froset[8]; //DRF

    message[39] = botset[0];
    message[40] = froset[6];
    message[41] = lefset[8]; //DFL

    message[42] = botset[6];
    message[43] = lefset[6];
    message[44] = behset[8]; //DLB

    message[45] = botset[8];
    message[46] = behset[6];
    message[47] = rigset[8]; //DBR

    for (int j = 0; j < 12; j++)
    {
        state[j][0] = message[2 * j];
        state[j][1] = message[2 * j + 1];
        state[j][2] = 0;
    }
    for (int j = 0; j < 8; j++)
    {
        state[j + 12][0] = message[3 * j + 24];
        state[j + 12][1] = message[3 * j + 1 + 24];
        state[j + 12][2] = message[3 * j + 2 + 24];
        state[j + 12][3] = 0;
    }
    for (int j = 0; j < 20; j++)
    {
        cout << state[j] << ' ';
    }
    cout << '\n'
         << endl;
}
void cube::play(char *chain)
{
    int i = 0;
    while (chain[i] != 0 && chain[i] != '\n')
    {
        if (chain[i] == ' ')
        {
            i++;
        }
        else
        {
            char operate = chain[i];
            int times = 0;
            if (chain[i + 1] == '\'')
                times = 3;
            else if (chain[i + 1] == ' ' || chain[i + 1] == '1' || chain[i + 1] == '\n' || chain[i + 1] == 0)
                times = 1;
            else if (chain[i + 1] == '2')
                times = 2;
            else if (chain[i + 1] == '3')
                times = 3;

            for (int j = 0; j < times; j++)
            {
                switch (operate)
                {
                case 'R':
                    R();
                    break;
                case 'r':
                    r();
                    break;
                case 'L':
                    L();
                    break;
                case 'l':
                    l();
                    break;
                case 'U':
                    U();
                    break;
                case 'u':
                    u();
                    break;
                case 'D':
                    D();
                    break;
                case 'F':
                    F();
                    break;
                case 'f':
                    f();
                    break;
                case 'd':
                    d();
                    break;
                case 'B':
                    B();
                    break;
                case 'b':
                    b();
                    break;
                case 'X':
                    X();
                    break;
                case 'Y':
                    Y();
                    break;
                case 'Z':
                    Z();
                    break;
                }
            }
            cout << operate << times;
            i += 2;
        }
    }
    cout << '\n';
}

void cube::display()
{
    char empty[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    cout << '\n';
    for (int i = 0; i < 9; i++)
    {
        if (i < 3)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << empty[3 * i + j] << ' ';
            }
            for (int j = 0; j < 3; j++)
            {
                cout << topset[3 * i + j] << ' ';
            }
            cout << '\n';
        }
        else if (i < 6)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << lefset[3 * i - 9 + j] << ' ';
            }
            for (int j = 0; j < 3; j++)
            {
                cout << froset[3 * i - 9 + j] << ' ';
            }
            for (int j = 0; j < 3; j++)
            {
                cout << rigset[3 * i - 9 + j] << ' ';
            }
            for (int j = 0; j < 3; j++)
            {
                cout << behset[3 * i - 9 + j] << ' ';
            }
            cout << '\n';
        }
        else
        {
            for (int j = 0; j < 3; j++)
            {
                cout << empty[3 * i - 18 + j] << ' ';
            }
            for (int j = 0; j < 3; j++)
            {
                cout << botset[3 * i - 18 + j] << ' ';
            }
            cout << '\n';
        }
    }
    cout << '\n';
}

//---------------------------------------heng xiang xuan zhuan-----------------------------------------

void cube::actxy(int level, int way) //(ceng shu,fang xiang)1==shunshi zhen  0==ni shi zhen
{
    int box[12], a, b;
    int in[9], out[9], t = 0, i;
    for (t = 0; t < 9; t++)
    {
        if (level == 0)
        {
            in[t] = topset[t];
            out[t] = in[t];
        }
        else if (level == 2)
        {
            in[t] = botset[t];
            out[t] = in[t];
        }
    }
    for (i = 0; i < 3; i++)
    {
        for (t = 0; t < 3; t++) //load data up
        {
            box[t] = lefset[t + 3 * level];
            box[t + 3] = froset[t + 3 * level];
            box[t + 6] = rigset[t + 3 * level];
            box[t + 9] = behset[t + 3 * level];
        }

        if (way == 1)
        {
            a = box[0];
            for (t = 0; t < 11; t++)
            {
                box[t] = box[t + 1];
            }
            box[11] = a;
            if (level == 0 && i == 1)
            {
                out[0] = in[6];
                out[1] = in[3];
                out[2] = in[0];
                out[3] = in[7];
                out[5] = in[1];
                out[6] = in[8];
                out[7] = in[5];
                out[8] = in[2];
                out[4] = in[4];
                for (t = 0; t < 9; t++)
                {
                    topset[t] = out[t];
                }
            }
            if (level == 2 && i == 1)
            {
                out[6] = in[0];
                out[3] = in[1];
                out[0] = in[2];
                out[7] = in[3];
                out[1] = in[5];
                out[8] = in[6];
                out[5] = in[7];
                out[2] = in[8];
                out[4] = in[4];
                for (t = 0; t < 9; t++)
                {
                    botset[t] = out[t];
                }
            }
        }
        else if (way == 0)
        {
            a = box[11];
            for (t = 11; t >= 0; t--)
            {
                box[t + 1] = box[t];
            }
            box[0] = a;
            if (level == 2 && i == 1)
            {
                out[0] = in[6];
                out[1] = in[3];
                out[2] = in[0];
                out[3] = in[7];
                out[5] = in[1];
                out[6] = in[8];
                out[7] = in[5];
                out[8] = in[2];
                out[4] = in[4];
                for (t = 0; t < 9; t++)
                {
                    botset[t] = out[t];
                }
            }
            if (level == 0 && i == 1)
            {
                out[6] = in[0];
                out[3] = in[1];
                out[0] = in[2];
                out[7] = in[3];
                out[1] = in[5];
                out[8] = in[6];
                out[5] = in[7];
                out[2] = in[8];
                out[4] = in[4];
                for (t = 0; t < 9; t++)
                {
                    topset[t] = out[t];
                }
            }
        }
        for (t = 0; t < 3; t++) //load data down
        {
            lefset[t + 3 * level] = box[t];
            froset[t + 3 * level] = box[t + 3];
            rigset[t + 3 * level] = box[t + 6];
            behset[t + 3 * level] = box[t + 9];
        }
    }
}
//-----------------------------------zong shen zhuan dong-------------------------------------------------
void cube::actxz(int level, int way)
{
    int box[12], a, b;
    int in[9], out[9], t = 0, i;
    for (t = 0; t < 9; t++)
    {
        if (level == 0)
        {
            in[t] = rigset[t];
            out[t] = in[t];
        }
        else if (level == 2)
        {
            in[t] = lefset[t];
            out[t] = in[t];
        }
    }
    for (i = 0; i < 3; i++)
    {
        for (t = 0; t < 3; t++) //load data up
        {
            box[t] = topset[2 + t * 3 - level];
            box[t + 3] = froset[2 + t * 3 - level];
            box[t + 6] = botset[2 + t * 3 - level];
            box[t + 9] = behset[6 - 3 * t + level];
        }

        if (way == 0)
        {
            a = box[11];
            for (t = 11; t >= 0; t--)
            {
                box[t + 1] = box[t];
            }
            box[0] = a;

            if (level == 2 && i == 1)
            {
                out[0] = in[6];
                out[1] = in[3];
                out[2] = in[0];
                out[3] = in[7];
                out[5] = in[1];
                out[6] = in[8];
                out[7] = in[5];
                out[8] = in[2];
                out[4] = in[4];
                for (t = 0; t < 9; t++)
                {
                    lefset[t] = out[t];
                }
            }
            else if (level == 0 && i == 1)
            {
                out[6] = in[0];
                out[3] = in[1];
                out[0] = in[2];
                out[7] = in[3];
                out[1] = in[5];
                out[8] = in[6];
                out[5] = in[7];
                out[2] = in[8];
                out[4] = in[4];
                for (t = 0; t < 9; t++)
                {
                    rigset[t] = out[t];
                }
            }
        }
        else if (way == 1)
        {
            a = box[0];
            for (t = 0; t < 11; t++)
            {
                box[t] = box[t + 1];
            }
            box[11] = a;
            if (level == 0 && i == 1)
            {
                out[0] = in[6];
                out[1] = in[3];
                out[2] = in[0];
                out[3] = in[7];
                out[5] = in[1];
                out[6] = in[8];
                out[7] = in[5];
                out[8] = in[2];
                out[4] = in[4];
                for (t = 0; t < 9; t++)
                {
                    rigset[t] = out[t];
                }
            }
            else if (level == 2 && i == 1)
            {
                out[6] = in[0];
                out[3] = in[1];
                out[0] = in[2];
                out[7] = in[3];
                out[1] = in[5];
                out[8] = in[6];
                out[5] = in[7];
                out[2] = in[8];
                out[4] = in[4];
                for (t = 0; t < 9; t++)
                {
                    lefset[t] = out[t];
                }
            }
        }
        for (t = 0; t < 3; t++) //load data down
        {
            topset[2 + t * 3 - level] = box[t];
            froset[2 + t * 3 - level] = box[t + 3];
            botset[2 + t * 3 - level] = box[t + 6];
            behset[6 - 3 * t + level] = box[t + 9];
        }
    }
}

//----------------------------------------zong heng yun dong----------------------------------------------
void cube::actyz(int level, int way) //(ceng shu,fang xiang)1==shun shi zhen  0==ni shi zhen
{
    int box[12], a, b;
    int in[9], out[9], t = 0, i;
    for (t = 0; t < 9; t++)
    {
        if (level == 0)
        {
            in[t] = froset[t];
            out[t] = in[t];
        }
        else if (level == 2)
        {
            in[t] = behset[t];
            out[t] = in[t];
        }
    }
    for (i = 0; i < 3; i++)
    {
        for (t = 0; t < 3; t++) //load data up
        {
            box[t] = topset[6 + t - 3 * level];
            box[t + 3] = rigset[t * 3 + level];
            box[t + 6] = botset[2 + 3 * level - t];
            box[t + 9] = lefset[8 - 3 * t - level];
        }

        if (way == 1)
        {
            a = box[11];
            for (t = 11; t >= 0; t--)
            {
                box[t + 1] = box[t];
            }
            box[0] = a;
            if (level == 0 && i == 1)
            {
                out[0] = in[6];
                out[1] = in[3];
                out[2] = in[0];
                out[3] = in[7];
                out[5] = in[1];
                out[6] = in[8];
                out[7] = in[5];
                out[8] = in[2];
                out[4] = in[4];
                for (t = 0; t < 9; t++)
                {
                    froset[t] = out[t];
                }
            }
            else if (level == 2 && i == 1)
            {
                out[6] = in[0];
                out[3] = in[1];
                out[0] = in[2];
                out[7] = in[3];
                out[1] = in[5];
                out[8] = in[6];
                out[5] = in[7];
                out[2] = in[8];
                out[4] = in[4];
                for (t = 0; t < 9; t++)
                {
                    behset[t] = out[t];
                }
            }
        }
        else if (way == 0)
        {
            a = box[0];
            for (t = 0; t < 11; t++)
            {
                box[t] = box[t + 1];
            }
            box[11] = a;
            if (level == 2 && i == 1)
            {
                out[0] = in[6];
                out[1] = in[3];
                out[2] = in[0];
                out[3] = in[7];
                out[5] = in[1];
                out[6] = in[8];
                out[7] = in[5];
                out[8] = in[2];
                out[4] = in[4];
                for (t = 0; t < 9; t++)
                {
                    behset[t] = out[t];
                }
            }
            else if (level == 0 && i == 1)
            {
                out[6] = in[0];
                out[3] = in[1];
                out[0] = in[2];
                out[7] = in[3];
                out[1] = in[5];
                out[8] = in[6];
                out[5] = in[7];
                out[2] = in[8];
                out[4] = in[4];
                for (t = 0; t < 9; t++)
                {
                    froset[t] = out[t];
                }
            }
        }
        for (t = 0; t < 3; t++) //load data down
        {
            topset[6 + t - 3 * level] = box[t];
            rigset[t * 3 + level] = box[t + 3];
            botset[2 + 3 * level - t] = box[t + 6];
            lefset[8 - 3 * t - level] = box[t + 9];
        }
    }
}
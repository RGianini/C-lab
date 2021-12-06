#include <stdlib.h>
#include <stdio.h>


//global-----------------------------------------------
void (*FuncPointer)(); //SM function pointer

int stimMtx[8]= {1,1,1,2,1,1,1,1};
// [0] interface nOK:0, interface OK:1
// [1] Pckt RX nOK: 0, Pckt RX OK: 1, Pckt nRX: 2

//prototypes-------------------------------------------
void StateLnkChk(void);       //1st state
void StateSndStart(void);     //2nd state
void StateSndCfg(void);       //3rd state
void StateSndKeepAlive(void); //4th state


//Functions-------------------------------------------
void StateLnkChk(void)
{
    system("PAUSE");
    printf("\n\n--------STATE: StateLnkChk ------------");
    int interfaceOK = stimMtx[0];
    int packtRX = stimMtx[1];

    if (interfaceOK){
            switch(packtRX){
                case 0:
                case 2:
                    {
                        printf("\nState link check nOK!>>>>>>\n\n");
                        break;
                    }
                case 1:
                    {
                        FuncPointer = StateSndStart;
                        printf("\nState link check OK!>>>>>>\n\n");
                        break;
                    }
                default:
                    {
                        FuncPointer = StateSndCfg;
                        break;
                    }
            }

    }else {
        printf("\nLink Problem detected. Restarting\n\n");
    }

}

void StateSndStart(void)
{
    system("PAUSE");
    printf("\n\n--------STATE: StateSndStart ------------");
    int interfaceOK = stimMtx[2];
    int packtRX = stimMtx[3];

    if (interfaceOK){
        switch(packtRX){
        case 0:
        case 2:
            {
                printf("\nFailure in Receiving the packet..\n\n");
                break;
            }
        case 1:
            {
                FuncPointer = StateSndCfg;
                printf("\nState Send Start OK!>>>>>>\n\n");
                break;
            }
        default:
            {
                FuncPointer = StateSndStart;
                break;
            }

        }
    }else {
        FuncPointer = StateLnkChk;
        printf("\nLink Problem detected. Restarting\n\n");
    }
}

void StateSndCfg(void)
{
    system("PAUSE");
    printf("\n\n--------STATE: StateSndCfg ------------");
    int interfaceOK = stimMtx[4];
    int packtRX = stimMtx[5];

    if (interfaceOK){
     switch (packtRX)
    {
        case 0:
            {
                printf("\nPacket received NOK... Trying\n\n");
                break;
            }
        case 1:
            {
                FuncPointer = StateSndKeepAlive;
                printf("\nPacket received OK. Sending KeepAlive\n\n");
                break;
            }
        case 2:
            {
                FuncPointer = StateSndStart;
                printf("\nNo answer. Going back to Send Start.\n\n");
                break;
            }
        default:
            {
                FuncPointer = StateSndCfg;
                break;
            }
    }
    }else {
        FuncPointer = StateLnkChk;
        printf("\nLink Problem detected. Restarting\n\n");
    }
}

void StateSndKeepAlive(void)
{
    system("PAUSE");
    printf("\n\n--------STATE: StateSndKeepAlive ------------");
    int interfaceOK = stimMtx[6];
    int packtRX = stimMtx[7];

    if (interfaceOK){
         switch (packtRX)
        {
            case 0:
            case 2:
                {
                    FuncPointer = StateSndStart;
                    printf("\nNo answer. Going back to Send Start.\n\n");
                    break;
                }
            case 1:
                {
                    printf("\nReceiving...\n\n");
                    system("PAUSE");
                    break;
                }
            default:
                FuncPointer = StateSndKeepAlive;
                break;
        }
    }else {
        FuncPointer = StateLnkChk;
        printf("\nLink Problem detected. Restarting\n\n");
    }
}


int main(void)
{
  FuncPointer = StateLnkChk; //initial state

  while(1)
  {
    (*FuncPointer)();
  }
}

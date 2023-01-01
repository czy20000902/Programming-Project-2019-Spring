//
//  main.m
//  ???
//
//  Created by zhm on 2019/6/9.
//  Copyright © 2019 zhm. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
extern  order rider[MaxPerson];

void GetToLocation(int index)
{
    int turn=0;
    if (rider[index].Next == NULL)//?????????,??????????
    {
        if(rider[index].customer[0]-rider[index].restaurant[0]==0||
                rider[index].customer[0]-rider[index].restaurant[0]==1||
                    rider[index].customer[0]-rider[index].restaurant[0]==-1)
        {
            turn = 1;
        }
        //???????
        if(rider[index].customer[1]%2==0)//??????????,?????
        {
            if(rider[index].customer[1]<=rider[index].restaurant[1]&&rider[index].customer[1]!=16)
                rider[index].customer[1]++;//?????????
            else
                rider[index].customer[1]--;//?????????
        }
        if(rider[index].customer[1]%2!=0&&turn==0)//???????
        {
            if(rider[index].customer[0]<rider[index].restaurant[0]-1&&rider[index].restaurant[0]%2==0)
            {
                rider[index].customer[0]++;
            }
            if(rider[index].customer[0]<rider[index].restaurant[0]&&rider[index].restaurant[0]%2!=0)
            {
                rider[index].customer[0]++;
            }
            if(rider[index].customer[0]>rider[index].restaurant[0]+1&&rider[index].restaurant[0]%2==0)
            {
                rider[index].customer[0]--;
            }
            if(rider[index].customer[0]>rider[index].restaurant[0]&&rider[index].restaurant[0]%2!=0)
            {
                rider[index].customer[0]--;
            }
        }
        if(rider[index].customer[1]%2!=0&&turn==1)//?????
        {
            if(rider[index].customer[1]>rider[index].restaurant[1])
            {
                rider[index].customer[1]--;
            }
            if(rider[index].customer[1]<rider[index].restaurant[1])
            {
                rider[index].customer[1]++;
            }
        }
        //??????
        if(rider[index].customer[1]==rider[index].restaurant[1]&&rider[index].customer[1]%2!=0&&turn==1)
        {
            if(rider[index].customer[0]>rider[index].restaurant[0])
                rider[index].customer[0]--;
            if(rider[index].customer[0]<rider[index].restaurant[0])
                rider[index].customer[0]++;
        }
    }
    //??????????????,????
    else if (rider[index].Next->delivering == 0)
    {
        if(rider[index].customer[0]-rider[index].Next->restaurant[0]==1||
           rider[index].customer[0]-rider[index].Next->restaurant[0]==-1)
        {
            turn=1;
        }
        if(rider[index].customer[1]%2==0&&turn==0)//????????
        {
            if(rider[index].customer[1]<=rider[index].Next->restaurant[1]&&rider[index].customer[1]!=16)
                rider[index].customer[1]++;//?????????
            else
                rider[index].customer[1]--;//?????????
        }
        //???????
        if(rider[index].customer[0]<rider[index].Next->restaurant[0]-1)
        {
            rider[index].customer[0]++;
        }
        if(rider[index].customer[0]>rider[index].Next->restaurant[0]+1)
        {
            rider[index].customer[0]--;
        }
        //?????,??????
        if(rider[index].customer[1]<rider[index].Next->restaurant[1]&&turn==1)
        {
            rider[index].customer[1]++;
        }
        if(rider[index].customer[1]>rider[index].Next->restaurant[1]&&turn==1)
        {
            rider[index].customer[1]--;
        }
    }
    //???????????????,????????
    else if (rider[index].Next->delivering == 1)
    {
  
        if(rider[index].customer[0]-rider[index].Next->customer[0]==1||
           rider[index].customer[0]-rider[index].Next->customer[0]==-1)
        {
            turn=1;
        }
        if(rider[index].customer[1]%2==0&&turn==0)//????????
        {
            if(rider[index].customer[1]<=rider[index].Next->customer[1]&&rider[index].customer[1]!=16)
                rider[index].customer[1]++;//?????????
            else
                rider[index].customer[1]--;//?????????
        }
        //???????
        if(rider[index].customer[0]<rider[index].Next->customer[0]-1)
        {
            rider[index].customer[0]++;
        }
        if(rider[index].customer[0]>rider[index].Next->customer[0]+1)
        {
            rider[index].customer[0]--;
        }
        //?????,??????
        if(rider[index].customer[1]<rider[index].Next->customer[1]&&turn==1)
        {
            rider[index].customer[1]++;
        }
        if(rider[index].customer[1]>rider[index].Next->customer[1]&&turn==1)
        {
            rider[index].customer[1]--;
        }
    }
}


#include<stdio.h>

int low=0,high=0;
int blocked[40]={0};
int clist[50]={0};
int bnum=0,cnum=0;
int mclicks=0;             /*will contain minimum clicks*/
int clicks[7]={0};          /*will calculate minclcicks for each of the set of situations*/
int curr_ch;                /*current channel*/


int min_clicks();
int get_digits(int x);
int init(int* x,int n);
int min_val(int* x,int n);
void get_data();
void channel_up(int i,int index);
void channel_down(int i,int index);
int min_clicks();


int main() {
  get_data();
  printf("\n%d\n",min_clicks());
}


int get_digits(int x) {             /*returns the number of digits in the channel when the channel is keyed in*/
    int count=0;
    while(x>0){
       count++;
       x/=10;
    }
return count;
}


int init(int* x,int n) {            /*to initialize the number of clicks to 0 for each of the procedures followed*/
    int i;
    for(i=0;i<n;i++)
       x[i]=0;
}


int min_val(int* x,int n) {         /*returns the minclicks value among all the procedures followed*/

    int min=x[0];
    int i;
    for(i=0;i<n;i++){
       if(x[i]<min)
           min=x[i];
    }
    return min;
}


void get_data() {                   /*Get the user data*/
 char low_high[10];
 char blocked_list[210];
 char channel_list[260];
 int i=0,j=0;

 gets(low_high);
 gets(blocked_list);
 gets(channel_list);
 while(low_high[i]!='\0'){          /*storing the min and max channel value */
  if(low_high[i]==32)
      j++;
  else if(j==0)
    low=low*10+(low_high[i]-48);
  else if(j==1)
    high=high*10+(low_high[i]-48);
  i++;
 }
 i=j=0;
 while(blocked_list[i]!='\0'){      /*for storing the list of blocked channels*/
     if(blocked_list[i]==32)
       bnum++;
     else
       blocked[bnum]=blocked[bnum]*10+(blocked_list[i]-48);
     i++;
 }
 i=0;
 while(channel_list[i]!='\0'){      /*for storing the channels to be viewed*/
     if(channel_list[i]==32)
       cnum++;
     else
       clist[cnum]=clist[cnum]*10+(channel_list[i]-48);
     i++;
 }
}


void channel_up(int i,int index) {        
     int j;
     while(curr_ch!=clist[i]){
         if(curr_ch==high)
            curr_ch=low;
         else
            curr_ch++;
         for(j=0;j<=bnum;j++){
            if(blocked[j]==curr_ch){
               if(curr_ch==high)
                  curr_ch=low;
               else
                  curr_ch++;
               j=0;
            }
         }
          clicks[index]++;
     }
}


void channel_down(int i,int index) {
     int j;
     while(curr_ch!=clist[i]){
         if(curr_ch==low)
            curr_ch=high;
         else
            curr_ch--;
         for(j=0;j<=bnum;j++){
            if(blocked[j]==curr_ch){
               if(curr_ch==low)
                  curr_ch=high;
               else
                   curr_ch--;
               j=0;
            }
         }
          clicks[index]++;
     }
}


int min_clicks() {
    int i;
    mclicks+=get_digits(clist[0]);     /*for the first channel, you will always key in the digits*/
    curr_ch=clist[0];
    for(i=1;i<=cnum;i++){               /*run loop from second channel to cnum*/
      init(clicks,8);                   /*initialize clicks to 0 at the beginning of every iteration*/

      clicks[0]=get_digits(clist[i]);
      /*end of part 1 - directly key in the digits*/

      curr_ch=clist[i-1];
      channel_up(i,1);
      /*end of part 2 - keep pressing up*/

      curr_ch=clist[i-1];
      channel_down(i,2);
      /*end of part 3 - keep pressing down*/

      curr_ch=low;
      clicks[3]+=get_digits(low);
      channel_down(i,3);
      /*end of part 4 - key in min value and go back*/

      curr_ch=high;
      clicks[4]+=get_digits(high);
      channel_up(i,4);
      /*end of part 5 - key in max value and go forward*/

     if(i>1){
      curr_ch=clist[i-2];
      clicks[5]++;
      channel_up(i,5);
     } else clicks[5]=10000;
      /*end of part 6 - press back and then keep pressing down*/

     if(i>1) {
      curr_ch=clist[i-2];
      clicks[6]++;
      channel_down(i,6);
     } else clicks[6]=10000;
      /*end of part 7 - press back and then keep pressing up*/

      mclicks+=min_val(clicks,7); /*increment minclicks by the min value among the procedures followed for current channel*/
    }
  return mclicks;
}

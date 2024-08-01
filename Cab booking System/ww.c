#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
int nuser;
int ndriver;
int nlocation;
int nmodel;

int dis_max[15][15];
char des1[15];
char loc1[15];

struct fare{
    char model[30];
	int fixed_fees;
	int mindis_fees;
	int maxdis_fees;
	int surge_fees;
	int cancl_fees;
	int adv_fees;
	int relaxation_fees;
}m[30];


struct cities{
    char cityname_[80];
}c[15];

struct drhistory
{
	float rating;
	char user[30];
	int adv;
	int otp;
	char date[10];
	
};

struct driver
{
 char name[30];
 int car;
 char model[30];
 int status;
 int capacity;
 int exp;
 float rating;
 int age;
 int rides;
 struct drhistory drhis[50];
 char loc[30];
 int phone;
}dr[50];



struct history
{
 char start[30];
 char drop[30];
 float fare;
 int car;
 char model[30];
 int adv;
 int otp;
 char date[10];
};

struct account
{
 char user[30];
 char password[30];
 char name[30];
 char gender[10];
 struct history his[100];
 int rides;
 int phone;
}a[50];

int check(char r[])
{
	int i;
	if (strcmp(r,"")==0)
	{
		printf("User name cannot be blank\n");
		return 0;
	}
	else
	{
	 for (i=0; i<50; i++)
	 {
	 	if(strcmp(r, a[i].user)==0)
	 	{
	 		printf("Username already taken\n");
	 		return 0;
		}
		else
		{
			return 1;
		}
	 }
   }
}

int loc(int nloc){
    char str1[20];
    int x,y,z=0,w=1,p=0;
    while(w)
    {
     for (y=0;y<nloc;y++)
     {
        printf("%s\n",c[y].cityname_);
     }
     printf("\nPlease Enter the location name from the above cities\n");
     //getchar();
     gets(str1);
     for (z=0;z<15;z++)
     {
        if(strcmp(c[z].cityname_,str1)==0){
                x=z;
                w=0;
                p=1;
                strcpy(loc1,str1);
                break ;
        }
        
     }
     if (p==0){
           printf("enter valid string\n");
     }
           
      
    }
    return x;
    
}

void advrating(int id)
{
	int i,j,ans,gg;
	for(i=0; i<50; i++)
	{
		if (a[id].his[i].adv==1)
		{
			printf("ID : %d\n", a[id].his[i].car);
			printf("Destination : %s\n", a[id].his[i].drop);
			printf("Fare : %f\n", a[id].his[i].fare);
			printf("Date : %s\n", a[id].his[i].date);
			float rating;
			printf("Enter your rating : \n");
			gg=1;
			while(gg)
    		{
    			scanf("%f", &rating);
    			if(rating<1.0 ||rating>5.0)
    			{
    				printf("Enter the values from 1 to 5 : ");
				}
				else
				{
					gg=0;
				}
			}
			for(j=0;j<50;j++)
			{
				if(dr[j].car==a[id].his[i].car)
				{
					ans = j;
				}
			}
			dr[ans].rating=((dr[ans].rating * (dr[ans].rides-1)) + rating)/dr[ans].rides;
			dr[ans].drhis[dr[ans].rides-1].rating = rating;
			dr[ans].drhis[dr[ans].rides-1].adv =2;
			a[id].his[i].adv=2;
			dr[ans].status=1;
			if(rating <= 2)
			{
				printf("Sorry for your bad experience, You can contact our company through email abc@gamil.com or dial 99999 for complain\n ");
			}
			else
			{
				printf("Thank you for your rating :)\n");
			}
			
			
		}
	}
}

void cancel(int id, int nmodel)
{
	int i,j,k,c=0,res;
	float cf;
	for(i=0; i<a[id].rides; i++)
	{
		if (a[id].his[i].adv==1)
		{
			c++;
			printf("ID : %d\n", a[id].his[i].car);
			printf("Destination : %s\n", a[id].his[i].drop);
			printf("Fare : %.2f\n", a[id].his[i].fare);
			printf("Date : %s\n", a[id].his[i].date);
			printf("For canceling this ride (with cancellation fee) press 1 or to go back press 2\n");
			scanf("%d", &res);
			if (res == 1)
			{
				for(j=0;j<nmodel;j++)
				{
					if (strcmp(a[id].his[i].model,m[j].model)==0)
					{
						cf = (float)m[j].cancl_fees;
					}
				}
				printf("The payment %.2f will be returned shortly with reduction of cancelation fees of %.2f\n",a[id].his[i].fare-cf,cf);
				a[id].his[i].adv=3;
				
			}
		}
    }
    if(c==0)
	{
    	printf("No cars were booked advance \n");
	}
}

int des(int nloc)
{
    char str1[20];
    int x,y,z=0,w=1,p=0;
    while(w)
    {
     for (y=0;y<nloc;y++)
     {
        printf("%s\n",c[y].cityname_);
     }
     printf("\nPlease Enter the destination name from the above cities\n");
     
     gets(str1);
     for (z=0;z<15;z++)
     {
        if(strcmp(c[z].cityname_,str1)==0){
                x=z;
                w=0;
                p=1;
                strcpy(des1,str1);
                break ;
        }
        
     }
     if (p==0){
           printf("enter valid string\n");
     }
           
      
    }
    return x;
    
}
int distance(int x,int y){
    return dis_max[x][y];
}

int surge(){
    int sum=0,i;
    for ( i=0;i<30;i++)
    {
        sum+=dr[i].status;
    }
    if(sum<15){
        return 1;
    }
    else{
        return 0;
    }
}


float fare(int d,int adv ,char model[] )
{
    float fare;
	int sur,i;
    sur=surge();
    for ( i=0;i<30;i++)
    {
        if(strcmp(m[i].model,model)==0 )
        {
            if (d<15)
            {
                fare=(m[i].fixed_fees)+(d*m[i].mindis_fees)+(sur*m[i].surge_fees)+(adv*m[i].adv_fees) ;
       return fare;
            }
            else{
                fare=(m[i].fixed_fees)+(d*m[i].maxdis_fees)+(sur*m[i].surge_fees)+(adv*m[i].adv_fees) ;
       return fare;
            }
        }
    }
}

int highrated(int drr[], int n)
{
	int i,ans;
	float max;
	max = dr[drr[0]].rating;
	ans = drr[0];
	for (i=1; i<n; i++)
	{
		if(dr[drr[i]].rating > max)
		{
			max = dr[drr[i]].rating;
			ans = i;
		}
	}
	return ans;
}


float rental_fare(int d,char model[] )
{
    float fare;
	int sur,i;
    sur=surge();
    for ( i=0;i<30;i++)
    {
        if(strcmp(m[i].model,model)==0 ){
		
        
                fare=(m[i].fixed_fees)+(d*m[i].maxdis_fees)+(sur*m[i].surge_fees)+(m[i].adv_fees)-m[i].relaxation_fees ;
                return fare;
            
        }
    }
}
void rental(int id,int nloc, int nmodel){
    int d,fa,res;
    char loc[30],des[30],model[30];
    printf("Welcome \n");
    printf("We only rent for distance greater then 200 km\n");
    printf("Enter the location\n");
    getchar();
    gets(loc);
    printf("\nEnter the destination\n");
    gets(des);
    printf("Enter the date : \n");
    char date[20];
    gets(date);
    printf("\nEnter the distance\n");
    scanf("%d",&d);
    int pr=2;
    while(pr){
        if (d>200){
            pr=0;
        }
        else{
            printf("This service is only for distance greater than 200 km\n");
            printf("Please Enter the distance again\n");
            scanf("%d",&d);
        }
    }
   
    
    int drl[50];
    int p=1;
    int i;
    for(i=0;i<nmodel;i++)
    {
    	printf("%s\n", m[i].model);
	}
	
    int count=0,n=0;
    getchar();
    while (p==1)
    {
      printf("\nEnter the model names\n");
      gets(model);
	  
      for(i=0;i<50;i++)
      {
    	if (dr[i].status==1)
    	{
    		count++;
    		if(strcmp(dr[i].model,model)==0)
    		{
    			drl[n]=i;
    			n++;
			}
		}
    	
	  }
	  if(n!=0)
	  {
	  	p=0;
	  }
	  if(count!=0&&n==0)
	  {
	  	printf("This model is not available\n ");
	  }
    }
    int ans;
    fa=rental_fare(d,model);
    ans = highrated(drl,n);
    printf("DRIVER FOUND\n");
    printf("ID : %d\n", dr[ans].car);
    printf("Name : %s\n", dr[ans].name);
    printf("Age : %d\n", dr[ans].age);
    printf("Experience : %d years\n", dr[ans].exp);
    printf("Average Rating : %.2f\n", dr[ans].rating);
    printf("The Fare will be : %d\n",fa);
    printf("To accept enter 1 and to reject enter 2\n");
    scanf("%d",&res);
    if(res==1)
    {
        printf("You have booked it sucessfully\n");
        printf("Please proceed for thr payment\n");
        printf(".......\n");
        printf("Payment sucessfull\n");
        a[id].rides++;
        int otp;
        time_t t;
    	srand(t);
    	otp=rand()%1000;
    	printf("\n%s\n",date);
    	printf("The otp is %d\n", otp);
    	printf("The Phone number of driver is %d\n", dr[ans].phone);
    	dr[ans].drhis[dr[ans].rides-1].otp=otp;
    	a[id].his[a[id].rides-1].otp=otp;
    	dr[ans].rides++;
    	a[id].his[a[id].rides-1].car = dr[ans].car;
    	strcpy(a[id].his[a[id].rides-1].drop, des);
    	strcpy(a[id].his[a[id].rides-1].date, date);
    	strcpy(dr[ans].drhis[dr[ans].rides-1].date, date);
    	a[id].his[a[id].rides-1].fare =(float) fa;
    	strcpy(a[id].his[a[id].rides-1].model, dr[ans].model);
    	strcpy(a[id].his[a[id].rides-1].start, loc);
    	dr[ans].status = 0;
    	a[id].his[a[id].rides-1].adv =1;
    	dr[ans].drhis[dr[ans].rides-1].adv=1;
		strcpy(dr[ans].drhis[dr[ans].rides-1].user, a[id].user);
    	printf("Do not forget to rate once the ride is over \n");
    	
    }
    else{
        printf("The ride is cancelled");
    }
    
}


void signup(int n) //remember to increase nuser
{
	int i;
	char r[30];
	printf("Enter the username : ");
    gets(r);
    if(check(r)==0)
    {
    	signup(n);
	}
	else
	
	{
		while(1)
		{
		   strcpy(a[n].user, r);
		   printf("Set password : ");
		   char p[30];
		   gets(p);
		   if (strcmp(p,"")==0)
		   {
		    	printf("Password cannot be blank\n");
		    	continue;
		    
		   }
		   else
		   {
		    	strcpy(a[n].password, p);
			    printf("Enter your name : \n");
		    	gets(a[n].name);
		    	printf("Enter your gender :\n");
		    	gets(a[n].gender);
		    	a[n].rides=0;
		    	printf("Enter your phone number : \n");
		    	scanf("%d",&a[n].phone);
		    	printf("\nAccount created succesfully Now Login to continue \n");
		    	
		    	break;
		   }  
	    }  
   }
}

int signin()
{
	char r[30];
	int i, z=0;
	char p[30];
	printf("Enter your username : \n");
	gets(r);
	for (i=0; i<50; i++)
	{
		if(strcmp(a[i].user,r)==0)
		{
		
		  while(strcmp(r,r)==0)
		  {
			  z++;
			  printf("Enter password :\n");
			  gets(p);
			  if(strcmp(p, a[i].password)==0)
			  {
			    	printf("Logged in Succesfully\n");
				    return(i);
				    break;
			  }
			  else
			  {
			    	printf("Password is wrong Try again\n");
			    	continue;
			  }
		   } 
	    }
    }
	if (z==0)
	{
		printf("No such username exist\n");
		signin();
	}
	
}

void booking(int id, int nmodel, int nloc)
{
	int d;
	time_t t;
	int x,y,otp;
	getchar();
	x=loc(nloc);
	
	y=des(nloc);
	char str[15];
	strcpy(str, loc1);
	char des[15];
	strcpy(des, des1);
	d=distance(x,y);
	int i;
	int drl[50];
	char model[30];
	printf("Enter the model you need from the following lists \n");
	for(i=0; i<nmodel; i++)
	{
		printf("%s\n", m[i].model);
	}
	int p=1;
	int n,count,ans;
	while(p==1)
	{
	
	  gets(model);
	  count =0;
	  n = 0;
	  ans;
	
	  for (i=0; i<50; i++)
	  {
		if(strcmp(dr[i].loc, str)==0 && dr[i].status == 1 )
		{
			count++; 
		    if(strcmp(dr[i].model, model)==0)
		    {
		   	    drl[n]=i;
		   	    n++;
		    }
				
		}
		
		
	  }
	  if (n==0 && count != 0)
	  {
	  	printf("No cars in this model is available Choose another model : \n");
	  	
	  }
	  else
	  {
	  	p=0;
	  }
    }
	if (count==0)
	{
		printf("SORRY NO CARS ARE AVAILABLE IN THE LOCATION\n");
    }
    else
    {
    	ans = highrated(drl,n);
    	printf("DRIVER FOUND\n");
    	printf("ID : %d\n", dr[ans].car);
    	printf("Name : %s\n", dr[ans].name);
    	printf("Age : %d\n", dr[ans].age);
    	printf("Experience : %d years\n", dr[ans].exp);
    	printf("Average Rating : %.2f\n", dr[ans].rating);
    	printf("Total charge = %f\n", fare(d,0,model));
    	printf("********\n");
    	printf("Press 1 to accept, Press 2 to cancel : \n");
    	int res;
    	scanf("%d",&res);
    	if (res ==1)
    	{
    		a[id].rides++;
    		srand(t);
    		otp=rand()%1000;
    		printf("The otp is %d\n", otp);
    		printf("The Phone number of driver is %d\n", dr[ans].phone);
    		dr[ans].drhis[dr[ans].rides-1].otp=otp;
    		a[id].his[a[id].rides-1].otp=otp;
    		dr[ans].rides++;
    		a[id].his[a[id].rides-1].car = dr[ans].car;
    		strcpy(a[id].his[a[id].rides-1].drop, des);
    		a[id].his[a[id].rides-1].fare =fare(d,0,model);
    		strcpy(a[id].his[a[id].rides-1].model, dr[ans].model);
    		strcpy(a[id].his[a[id].rides-1].start, str);
    		dr[ans].status = 0;
    		int gg=0;
    		printf("\nEnjoy your ride. When the ride is over press 1\n");
    		
    		while(gg!=1)
    		{
    			scanf("%d", &gg);
			}
			
			dr[ans].status = 1;
			strcpy(dr[ans].loc, des);
			strcpy(dr[ans].drhis[dr[ans].rides-1].user, a[id].user);
    		float rating;
    		a[id].his[a[id].rides-1].adv =0 ;
    		dr[ans].drhis[dr[ans].rides-1].adv=0;
    		a[id].his[a[id].rides-1].adv=0;
    		printf("Proceed payment through cash or through UPI id 2022\n");
    		printf("..........\n");
    		printf("Payment Successful");
    		printf("\nRate your experience(1 t0 5) : ");
    		while(gg==1)
    		{
    			scanf("%f", &rating);
    			if(rating<1 ||rating>5)
    			{
    				printf("Enter the values from 1 to 5 : ");
				}
				else
				{
					gg=0;
				}
			}
			dr[ans].rating=((dr[ans].rating * (dr[ans].rides-1)) + rating)/dr[ans].rides;
			dr[ans].drhis[dr[ans].rides-1].rating = rating;
			if(rating <= 2)
			{
				printf("Sorry for your bad experience, You can contact our company through email abc@gamil.com or dial 99999 for complain\n ");
			}
			else
			{
				printf("Thank you for your rating:), share your experience through email abc@gamil.com or dial 99999 \n");
			}
			
			
		}
	
    	
	}
	
	
	
	
	
}

void advance(int id, int nmodel, int nloc)
{

	int d;
	time_t t;
	int x,y;
	getchar();
	x=loc(nloc);
	y=des(nloc);
	char str[15];
	strcpy(str, loc1);
	char des[15];
	strcpy(des, des1);
	d=distance(x,y);
	char date[10];
	printf("Enter the date for your booking :\n");
	gets(date);
	int i;
	int drl[50];
	char model[30];
	int otp;
	printf("Enter the model you need from the following lists \n");
	for(i=0; i<nmodel; i++)
	{
		printf("%s\n", m[i].model);
	}
	int p=1;
	int n,count,ans;
	while(p==1)
	{
	
	  gets(model);
	  count =0;
	  n = 0;
	  ans;
	
	  for (i=0; i<50; i++)
	  {
		if(strcmp(dr[i].loc, str)==0 && dr[i].status == 1 )
		{
			count++; 
		    if(strcmp(dr[i].model, model)==0)
		    {
		   	    drl[n]=i;
		   	    n++;
		    }
				
		}
		
		
	  }
	  if (n==0 && count != 0)
	  {
	  	printf("No cars in this model is available Choose another model : \n");
	  	
	  }
	  else
	  {
	  	p=0;
	  }
    }
	if (count==0)
	{
		printf("SORRY NO CARS ARE AVAILABLE IN THE LOCATION\n");
    }
    else
    {
    	ans = highrated(drl,n);
    	printf("DRIVER FOUND\n");
    	printf("ID : %d\n", dr[ans].car);
    	printf("Name : %s\n", dr[ans].name);
    	printf("Age : %d\n", dr[ans].age);
    	printf("Experience : %d years\n", dr[ans].exp);
    	printf("Average Rating : %.2f\n", dr[ans].rating);
    	printf("Total charge = %f\n", fare(d,1,model));
    	printf("********\n");
    	printf("Press 1 to accept, Press 2 to cancel : \n");
    	int res;
    	scanf("%d",&res);
    	if (res ==1)
    	{
    		a[id].rides++;
    		dr[ans].rides++;
    		a[id].his[a[id].rides-1].car = dr[ans].car;
    		strcpy(a[id].his[a[id].rides-1].drop, des);
    		srand(t);
    		otp=rand()%1000;
    		printf("\n%s\n", date);
    		printf("The otp is %d\n", otp);
    		dr[ans].drhis[dr[ans].rides-1].otp=otp;
    		a[id].his[a[id].rides-1].otp=otp;
    		a[id].his[a[id].rides-1].fare =fare(d,1,model);
    		strcpy(a[id].his[a[id].rides-1].date, date);
    	    strcpy(dr[ans].drhis[dr[ans].rides-1].date, date);
    		strcpy(a[id].his[a[id].rides-1].model, dr[ans].model);
    		strcpy(a[id].his[a[id].rides-1].start, str);
    		dr[ans].status = 0;
    		int gg=0;
    		printf("Proceed advance payment through UPI id 2022\n");
    		printf("..........\n");
    		printf("Payment Successful\n");
    		printf("The otp is %d\n", otp);
    		printf("The Phone number of driver is %d\n", dr[ans].phone);
    		a[id].his[a[id].rides-1].adv =1;
    		dr[ans].drhis[dr[ans].rides-1].adv=1;
			strcpy(dr[ans].loc, des);
			strcpy(dr[ans].drhis[dr[ans].rides-1].user, a[id].user);
    		printf("Do not forget to rate once the ride is over \n");

		}    	
	}	
}

void viewcity(nloc)
{
	int i;
	for(i=0;i<nloc;i++)
	{
		printf("%s\n",c[i].cityname_);
	}
}

void editdriver(int ndriver, int nloc, int nmod)
{
	printf("Write the name of driver : \n");
	gets(dr[ndriver].name);
	printf("\nPlease Enter the Destination name from the above cities\n");
	int i;
    for(i=0;i<nloc;i++)
    {
    	printf("%s \n", c[i].cityname_);
	}
    gets(dr[ndriver].loc);
    printf("Enter the model you need from the following lists \n");
	for(i=0; i<nmod; i++)
	{
		printf("%s\n", m[i].model);
	}
	gets(dr[ndriver].model);
	printf("Enter the age of driver : \n");
	scanf("%d", &dr[ndriver].age);
	printf("Enter the car id : ");
	int id,c=0,gg=1;
	while(gg)
	{
	 scanf("%d", &id);
	 for(i=0;i<ndriver;i++)
	 {
		if(id==dr[i].car)
		{
			c++;
		}
	 } 
	 if(c==0)
	 {
	 	gg=0;
	 }
	 else
	 {
	 	printf("ID already exist try again\n");
	 }
    }
    dr[ndriver].car=id;
    printf("Enter car capacity : \n");
    scanf("%d",&dr[ndriver].capacity);
    printf("Enter the experience of driver : \n");
    scanf("%d",&dr[ndriver].exp);
    printf("Enter mobile number : ");
    scanf("%d",&dr[ndriver].phone);
    printf("Driver edited successfully\n");
}

void viewdrhis(int i)
{
	int j;
	printf("Name : %s\n", dr[i].name);
	printf("ID : %d\n", dr[i].car);
	printf("No. of rides taken : %d\n",dr[i].rides);
	printf("Experience : %d years\n",dr[i].exp);
	printf("Avg rating : %f\n", dr[i].rating);
	printf("Phone no. : %d\n", dr[i].phone);
	printf("Status : %d\n", dr[i].status);
	printf("Current Location : %s\n", dr[i].loc);
	for(j=0;j<dr[i].rides;j++)
	{
		printf("%d\n",j+1 );
		printf("User : %s\n", dr[i].drhis[j].user);
		
		if (dr[i].drhis[j].adv==1){
			printf("Advance and booked\n");
			printf("Date Schelduled : %s", dr[i].drhis[j].date);
	    }
	    else if(dr[i].drhis[j].adv==2){
	    	printf("Advance and completed \n");
	    	printf("Rating : %f\n", dr[i].drhis[j].rating);
	    	printf("Date Schelduled : %s", dr[i].drhis[j].date);
		}
		else if(dr[i].drhis[j].adv==3){
			printf("Cancelled\n");
			printf("Date Schelduled : %s", dr[i].drhis[j].date);
		}
		else{
			printf("Rating : %f\n", dr[i].drhis[j].rating);
		}
	}
	
}	
void editmodel(int nmode)
{
	printf("Enter the model name : \n");
	char c[15];
	gets(c);
	int i,nmod;
	for(i=0;i<nmode;i++)
	{
		if (strcmp(m[i].model,c)==0)
		{
			nmod = i;
		}
	}
	printf("Enter the maxdistance fee : \n");
	scanf("%d", &m[nmod].maxdis_fees);
	printf("Enter min distance fee : \n");
	scanf("%d", &m[nmod].mindis_fees);
	printf("Enter fixed fee : \n");
	scanf("%d", &m[nmod].fixed_fees);
	printf("Enter cancellation fee : \n");
	scanf("%d", &m[nmod].cancl_fees);
	printf("Enter advanced fees : \n");
	scanf("%d", &m[nmod].adv_fees);
	printf("Enter relaxation fees : \n");
	scanf("%d", &m[nmod].relaxation_fees);
	printf("Enter surge fees : \n");
	scanf("%d", &m[nmod].surge_fees);
	printf("Model edited succesfully\n");
}

void changestatus(int i)
{
	printf("Press 0 to turn off ride and 1 to turn on ride : \n");
	int n;
	scanf("%d",&n);
	if (n==0)
	{
		printf("Contacting Manager \n");
		printf("................\n");
		dr[i].status=0;
    }
    else if(n==1)
    {
    	dr[i].status=1;
	}
	else
	{
		printf("Give a valid number");
	}

}

void viewfare(int nmode)
{
	int i;
	for(i=0; i<nmode; i++)
	{
		printf("%s\n", m[i].model);
	}
	printf("Enter the model name : \n");
	char c[15];
	gets(c);
	int nmod;
	for(i=0;i<nmode;i++)
	{
		if (strcmp(m[i].model,c)==0)
		{
			nmod = i;
		}
	}
	printf("Fixed Fee : %d\n", m[nmod].fixed_fees);
	printf("Advance Fee : %d\n", m[nmod].adv_fees);
	printf("Cancellation Fee : %d\n", m[nmod].cancl_fees);
	printf("Long distance Fee : %d\n", m[nmod].maxdis_fees);
	printf("Short distance Fee : %d\n", m[nmod].mindis_fees);
	printf("Relaxation Fee : %d\n", m[nmod].relaxation_fees);
	printf("Surge Fee : %d\n", m[nmod].surge_fees);
}

int drlogin()
{
	int num;
	int i, z=0;
	int id;
	printf("Enter your mobile number : \n");
	scanf("%d",&num);
	for (i=0; i<50; i++)
	{
		if(num == dr[i].phone)
		{
		
		  while(1)
		  {
			  z++;
			  printf("Enter id :\n");
			  scanf("%d", &id);
			  if(dr[i].car==id)
			  {
			    	printf("Logged in Succesfully\n");
				    return(i);
				    break;
			  }
			  else
			  {
			    	printf("ID is wrong Try again\n");
			    	continue;
			  }
		   } 
	    }
    }
	if (z==0)
	{
		printf("No such driver exist\n");
		signin();
	}
	
}

void adddriver(int ndriver, int nmodel, int  nloc)//dont forget to ndriver++
{
	printf("Write the name of driver : \n");
	gets(dr[ndriver].name);
	printf("\nPlease Enter the Destination name from the above cities\n");
	int i;
    for(i=0;i<nloc;i++)
    {
    	printf("%s \n", c[i].cityname_);
	}
    gets(dr[ndriver].loc);
    printf("Enter the model you need from the following lists \n");
	for(i=0; i<nmodel; i++)
	{
		printf("%s\n", m[i].model);
	}
	gets(dr[ndriver].model);
	printf("Enter the age of driver : \n");
	scanf("%d", &dr[ndriver].age);
	printf("Enter the car id : ");
	int id,c=0,gg=1;
	while(gg)
	{
	 scanf("%d", &id);
	 for(i=0;i<ndriver;i++)
	 {
		if(id==dr[i].car)
		{
			c++;
		}
	 } 
	 if(c==0)
	 {
	 	gg=0;
	 }
	 else
	 {
	 	printf("ID already exist try again\n");
	 }
    }
    dr[ndriver].car=id;
    printf("Enter car capacity : \n");
    scanf("%d",&dr[ndriver].capacity);
    int j;
    dr[ndriver].status=1;
    dr[ndriver].rating=0;
    dr[ndriver].rides=0;
    printf("Enter the experience of driver : \n");
    scanf("%d",&dr[ndriver].exp);
    printf("Enter mobile number : ");
    scanf("%d",&dr[ndriver].phone);
    printf("Driver added successfully\n");
    printf("Driver ID is %d\n", ndriver);
}

void userhis(int id)
{
	int i;
	printf("Name : %s\n", a[id].name);
	printf("Gender : %s\n", a[id].gender);
	printf("Phone no. : %d\n", a[id].phone);
	printf("No. of rides : %d\n", a[id].rides);
	for (i=0;i<a[id].rides;i++)
	{
		printf("%d\n", i+1);
		printf("Starting point : %s\n", a[id].his[i].start);
		printf("Destination : %s\n", a[id].his[i].drop);
		printf("Car ID : %d\n", a[id].his[i].car);
		printf("Car model : %s\n", a[id].his[i].model);
		printf("OTP : %d\n", a[id].his[i].otp);
		printf("Fare : %f\n", a[id].his[i].fare);
		if (a[id].his[i].adv==1){
			printf("Advance \n");
			printf("Date Schelduled : %s", a[id].his[i].date);
	    }
	    else if(a[id].his[i].adv==2){
	    	printf("Advance Journey Completed\n");
	    	printf("Date Schelduled : %s", a[id].his[i].date);
		}
		else if(a[id].his[i].adv==3){
			printf("Cancelled\n");
			printf("Date Schelduled : %s", a[id].his[i].date);
		}
		
	}
	
} 

void addmodel(int nmod)
{
	printf("Enter the model name : \n");
	gets(m[nmod].model);
	printf("Enter the maxdistance fee : \n");
	scanf("%d", &m[nmod].maxdis_fees);
	printf("Enter min distance fee : \n");
	scanf("%d", &m[nmod].mindis_fees);
	printf("Enter fixed fee : \n");
	scanf("%d", &m[nmod].fixed_fees);
	printf("Enter cancellation fee : \n");
	scanf("%d", &m[nmod].cancl_fees);
	printf("Enter advanced fees : \n");
	scanf("%d", &m[nmod].adv_fees);
	printf("Enter relaxation fees : \n");
	scanf("%d", &m[nmod].relaxation_fees);
	printf("Enter surge fees : \n");
	scanf("%d", &m[nmod].surge_fees);
	printf("Model added succesfully\n");
}
void addloc(int nloc)
{
	printf("Enter the name of the city : \n");
	gets(c[nloc].cityname_);
	int i;
	for(i=0;i<nloc;i++)
	{
		printf("Enter the distance from %s : \n", c[i].cityname_);
		scanf("%d", &dis_max[i][nloc]);
		dis_max[nloc][i]=dis_max[i][nloc];
	}
	dis_max[nloc][nloc]=0;
}

void user()
{
	int id;
	int res1;
	while(1){
	
	  printf("Welcome!!!\n Press 1 to sign in, 2 to sign up,Press any other number to exit\n");
	  scanf("%d", &res1);
	  getchar();
	  if(res1==2)
	  {
		signup(nuser);
		nuser++;
		printf("You have signed up sucessfully. \n Please signin\n");
		continue;
	  }
	  else if(res1==1)
	  {
		id=signin();
		int a=1;
		while(a){
		
		  printf("\n\nPress 1 to Book a cab \nPress 2 for advance booking\nPress 3 for renting a cab\nPress 4 to rate your previously advance booked cab\n");
		  printf("Press 5 to cancelation\nPress 6 to view history\nPress any other number to log out\n");
		  int res2;
		  scanf("%d", &res2);
		  if(res2==1)
		  {
	  		booking(id, nmodel, nlocation);
	  		continue;
		  }
		  else if(res2==2)
		  {
		  	advance(id,nmodel,nlocation);
		  	continue;
		  }
		  else if(res2==3)
		  {
		  	rental(id,nlocation,nmodel);
		  	continue;
		  }
		  else if(res2==4)
		  {
		  	advrating(id);
		  	continue;
		  }
		  else if(res2==5)
		  {
		  	cancel(id,nmodel);
		  	continue;
		  }
		  else if(res2==6)
		  {
		  	userhis(id);
		  	continue;
		  }
		  else{
		  	a=0;
		  }
	    }
	    break;
      }
	  else
	  {
		break;
	  }
    }
}

void admin()
{
	char user[30], pass[30];
	while(1)
	{
	  printf("Enter the user name :\n");
	  gets(user);
	  printf("Enter password : \n");
	  gets(pass);
	  if(strcmp(user, "admin")==0 && strcmp(pass, "varun")==0)
	  {
	  	int b=1;
	  	while(b)
	  	{
	  		printf("\n\nWelcome\nPress 1 to Add driver\nPress 2 to Edit driver\nPress 3 to Add city\nPress 4 to Add model\nPress 5 to edit fare\n");
	  		printf("Press 6 to view driver history\nPress 7 to view fares\nPress 8 to view available locations\nPress any other number to log out\n");
	  		int res1;
	  		scanf("%d", &res1);
	  		getchar();
	  		if(res1==1)
	  		{
	  			adddriver(ndriver,nmodel,nlocation);
	  			ndriver++;
			}
			else if(res1==2)
			{
				int j;
				printf("Enter the driver number you need to edit : \n");
				scanf("%d", &j);
				getchar();
				editdriver(j,nlocation,nmodel);
			}
			else if(res1==3)
			{
				addloc(nlocation);
				nlocation++;
			}
			else if(res1==4)
			{
				addmodel(nmodel);
				nmodel++;
			}
			else if(res1==5)
			{
				editmodel(nmodel);
			}
			else if(res1==6)
			{
				printf("Enter driver number : (1 to 50)\n");
				int x;
				scanf("%d",&x);
				getchar();
				viewdrhis(x);
			}
			else if(res1==7)
			{
				viewfare(nmodel);
			}
			else if(res1==8)
			{
				viewcity(nlocation);
			}
			else
			{
				b=0;
			}
	    }
		break;
	  }
	  else{
	  	printf("Invalid Log in\n press 1 to exit 2 to try again\n");
	  	int res2;
	  	scanf("%d", &res2);
	  	getchar();
	  	if(res2==2)
	  	{
	  		continue;
	    }
	    else
	    {
	    	break;
		}
	  }
    }
}

void driver()
{
	int i;
	i=drlogin();
	while(1)
	{
		printf("\n\nPress 1 to view history\nPress 2 to change status\nPress any other number to logout\n");
		int res1;
		scanf("%d",&res1);
		getchar();
		if(res1==1)
		{
			viewdrhis(i);
			continue;
		}
		else if(res1 ==2)
		{
			changestatus(i);
			continue;
		}
		else
		{
			break;
		}
		
	}
}

int main()
{
	int o;
	int i;
	
	FILE* fptr=fopen("distance.txt","r");
    fread(dis_max,sizeof(int),15*15,fptr);
	fclose(fptr);
	FILE* ptr=fopen("global.txt","r");
	fscanf(ptr,"%d %d %d %d",&nuser,&ndriver,&nlocation,&nmodel);
	fclose(ptr);
	FILE* file2 = fopen("city.txt","r");
	for(i=0;i<nlocation+1;i++)
	{
		fread(&c[i], sizeof(struct cities), 1, file2);
	}
	fclose(file2);
	
	FILE* file=fopen("user.txt","r");
	for (i=0;i<nuser;i++)
	{
		fread(&a[i], sizeof(struct account), 1, file);
	}
	fclose(file);
	FILE* file1=fopen("driver.txt", "r");
	for (i=0;i<ndriver;i++)
	{
		fread(&dr[i], sizeof(struct driver), 1, file1);
	}
	fclose(file1);
    FILE* file3=fopen("fare.txt","r");
	for (i=0;i<nmodel;i++)
	{
		fread(&m[i], sizeof(struct fare), 1, file3);
	}
	fclose(file3);
	while(1){
        int res11;
        printf("Enter 1 for user :\n");
        printf("Enter 2 for admin :\n");
        printf("Enter 3 for driver\n");
        printf("Enter any other number to exit\n");
        scanf("%d",&res11);
        getchar();
        if (res11 == 1){
            user();
            continue;
        }
        else if(res11 == 2){
            admin();
            continue;
        }
        else if(res11 ==3){
            driver();
            continue;
        }
        else{
            break;
        }
	}
	fptr=fopen("distance.txt","w");
	fwrite(dis_max,sizeof(int),15*15,fptr);
	fclose(fptr);
	ptr=fopen("global.txt","w");
	fprintf(ptr,"%d %d %d %d",nuser,ndriver,nlocation,nmodel);
	fclose(ptr);
	file=fopen("user.txt","w");
	for (i=0;i<nuser;i++)
	{
		fwrite(&a[i], sizeof(struct account), 1, file);
	}
	fclose(file);
	file1=fopen("driver.txt", "w");
	for (i=0;i<ndriver;i++)
	{
		fwrite(&dr[i], sizeof(struct driver), 1, file1);
	}
	fclose(file1);
	file2=fopen("city.txt","w");
	for (i=0;i<nlocation;i++)
	{
		fwrite(&c[i], sizeof(struct cities), 1, file2);
	}
	fclose(file2);
	file3=fopen("fare.txt","w");
	for (i=0;i<nmodel;i++)
	{
		fwrite(&m[i], sizeof(struct fare), 1, file3);
	}
	fclose(file3);

	return 0;
	
}


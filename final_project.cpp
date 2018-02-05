#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

double pi=3.14159265352;
double error=0.1;
double delta=5.0;

double deg2rad (double degrees) 
{
    return degrees * pi / 180.0;
}
double distance(double x1,double y1,double x2,double y2)
{
    double R = 6371e3; // metres
	double fi1 = deg2rad(x1);
	double fi2 = deg2rad(x2);
	double deltafi = deg2rad(x2-x1);
	double deltalanda = deg2rad(y2-y1);
	double a = sin(deltafi/2.0) * sin(deltafi/2.0) + cos(fi1) * cos(fi2) * sin(deltalanda/2.0) * sin(deltalanda/2.0);
	double c = 2.0 * atan2(sqrt(a), sqrt(1-a));
	double d = R * c;
	return d;
}

int main(int argc, char** argv) 
{
	int n_line=0;
	double x,y,last_x,last_y,time,last_time,feet,last_feet,h,dis,delta_t,v,v_min,v_max,segment_start,segment_end;
	int ch=1,last_ch=10;
	//////////////////////////////////
	while(n_line<6)
	{
		ch=getchar();
		if(ch==10)
			n_line++;
	}
	n_line=1;
	if(scanf("%lf,",&last_x)>0)
	{
		scanf("%lf,",&last_y);
		scanf("%lf,",&h);		//0
		scanf("%lf,",&last_feet);
		scanf("%lf,",&last_time);
		scanf("%lf-",&h);		//year
		scanf("%lf-",&h);	//month
		scanf("%lf,",&h);		//day
		scanf("%lf:",&h);		//hour
		scanf("%lf:",&h);		//minutes
		scanf("%lf",&h);		//second
		segment_start=last_time;
		time=last_time;
		if(scanf("%lf,",&x)>0)
		{
			scanf("%lf,",&y);
			scanf("%lf,",&h);		//0
			scanf("%lf,",&feet);
			scanf("%lf,",&time);
			scanf("%lf-",&h);		//year
			scanf("%lf-",&h);	//month
			scanf("%lf,",&h);		//day
			scanf("%lf:",&h);		//hour
			scanf("%lf:",&h);		//minutes
			scanf("%lf",&h);		//second
			delta_t=(time-last_time)*86400.0;
			dis=distance(last_x,last_y,x,y);
			v=dis/delta_t;
			v_max=v;
			v_min=v;
			//printf("delta_t=%f--dis=%f--v=%f--v_min=%f--v_max=%f\n",delta_t,dis,v,v_min,v_max);
		}
	}
	//printf("delta_t=%f--dis=%f--v=%f--v_min=%f--v_max=%f\n",last_time,time,delta_t,dis,v,v_min,v_max);
	while(scanf("%lf,",&x)>0)
	{
		last_x=x;
		last_y=y;
		last_feet=feet;
		last_time=time;
		//////////////////////////////////////////////
		scanf("%lf,",&y);
		scanf("%lf,",&h);		//0
		scanf("%lf,",&feet);
		scanf("%lf,",&time);
		scanf("%lf-",&h);		//year
		scanf("%lf-",&h);	//month
		scanf("%lf,",&h);		//day
		scanf("%lf:",&h);		//hour
		scanf("%lf:",&h);		//minutes
		scanf("%lf",&h);		//second
		delta_t=(time-last_time)*86400.0;
		dis=distance(last_x,last_y,x,y);
		v=dis/delta_t;
		//printf("delta_t=%f--dis=%f--v=%f--v_min=%f--v_max=%f\n",delta_t,dis,v,v_min,v_max);
			if(v>v_max)
			{
				if(v-v_min<=error)
					v_max=v;
				else
				{
					segment_end=last_time;
					printf("%d::%f-----%f-------->%f\n",n_line,segment_start,segment_end,((segment_end-segment_start)*86400.0));
					segment_start=segment_end;
					v_min=v;
					v_max=v;
					n_line++;
				}
			}
			else if(v<v_min)
			{
				if(v_max-v<=error)
					v_min=v;
				else
				{
					segment_end=last_time;
					printf("%d::%f-----%f-------->%f\n",n_line,segment_start,segment_end,((segment_end-segment_start)*86400.0));
					segment_start=segment_end;
					v_min=v;
					v_max=v;
					n_line++;
				}
			}
		//printf("delta_t=%f ,, dis=%f  ,, v=%f\n",delta_t,dis,v);
	}
	return 0;
}

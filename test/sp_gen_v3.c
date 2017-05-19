#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <string.h>
#define VDD 1.8
#define LOAD 10.0
#define max 128


// ============ Please edit the input vector ============
// the number of patterns
int pattern_number = 128 ;
double period = 3.0 ; //ns
// input patterns
int A0[] = {1,1,1,0,1} ;
int A1[max] = {1,1,1,1,1} ;
int A2[max] = {1,1,0,1,1} ;
int B0[max] = {1,0,0,0,1} ;
int B1[max] = {1,0,0,1,1} ;
int B2[max] = {1,1,0,1,1} ;
int CIN[max]= {1,0,1,1,1} ;
// golden output patterns
int AS0[max] = {1,1,0,1,1} ;
int AS1[max] = {1,1,0,0,1} ;
int AS2[max] = {1,0,1,1,1} ;
int ACOUT[max]={0,1,0,1,1} ;
// Set to 1 if you want to patch pex result file
int patch_pex_file = 1 ; // Yes:1 No:0
//=======================================================
int data[128][128];     //順序資料
int flag[128][128]={0}; //旗標
int count=0;
//============== DO NOT MODIFY =================

void pattern_init(){
    int input=0;
    for(int i=0;i<pattern_number;i++)
        flag[i][i]=1;
    
    for(int i=0;i<(pattern_number*(pattern_number-1));i++){
        //init input function with input
        A0[i] = (input>>6)%2;
        A1[i] = (input>>5)%2;
        A2[i] = (input>>4)%2;
        B0[i] = (input>>3)%2;
        B1[i] = (input>>2)%2;
        B2[i] = (input>>1)%2;
        CIN[i]= (input)%2;
        //std::cout<<"line"<<std::setw(2)<<i+1<<": "<<A0[i]<<A1[i]<<A2[i]<<B0[i]<<B1[i]<<B2[i]<<CIN[i]<<std::endl;
        //==============================
        for(int j=pattern_number-1;j>=0;j--){
            if(flag[input][j]==0){
                flag[input][j]=1;
                data[input][j]=++count;
                input=j;
                break;
            }
        }
    }
}







//============== DO NOT MODIFY =================

double max_sim_time ;
void gen_vec ( FILE * out , char * name , int val[] , int len , double period ) ;
int check ( char * item ) ;
void gen_tg ( FILE * out , char * in_name , char * out_name ) ;

int main( int argv , char ** argc ) {
    pattern_init();
	int i ;
	FILE * pex ;
	FILE * out ;
	time_t now ;
	time ( &now ) ;
	char pex_order [14][64] ;
	char token [1024] ;
	int read_successful = 0 ;
	max_sim_time = 0 ;

	// check input argument format
	if ( argv != 2 ) {
		printf ( "Error:\nUsage:\n ./sp_gen.exe your_sp_file.sp\n" ) ;
		return 0 ;
	}

	// open file
	pex = fopen ( "ADDER3.pex.netlist" , "r" ) ;
	out = fopen ( argc[1] , "w" ) ;

	// check pex file open successfully
	if ( pex == NULL ) {
		printf ( "Error:\nFile \"ADDER3.pex.netlist\" not found.\n" ) ;
		return 0 ;
	}

	// read pex
	while ( fscanf ( pex , "%s" , token ) != EOF ) {
		if ( !strcmp ( ".subckt" , token ) ) {
			for ( i = 0 ; i < 14 ; i ++ ) {
				fscanf ( pex , "%s" , pex_order[i] ) ;
				// check the names of ports here
				if ( ! check (pex_order[i]) ) {
					printf ( "Error:\n%s: Nothing match.\n" , pex_order[i] ) ;
					return 0 ;
				}
			}
			read_successful = 1 ;
		}
	}
	if ( !read_successful ) {
		printf ( "Error:\nFile \"ADDER3.pex.netlist\" format error.\n" ) ;
		return 0 ;
	}


	// check output file open successfully
	if ( out == NULL ) {
		printf ( "Error:\nFile \"%s\" can not open for write.\n" , argc[1] ) ;
		return 0 ;
	}

	// print header
	fprintf ( out , "* This spice file is generated by sp_gen\n" ) ;
	fprintf ( out , "* %s\n" , ctime ( &now ) ) ;
	fprintf ( out , ".include \"ADDER3.pex.netlist\"\n" ) ;
	fprintf ( out , ".lib \"cic018.l\" tt\n" ) ;
	fprintf ( out , "\n" ) ;

	// include instantiate ADDER3
	fprintf ( out , "XADDER3" ) ;
	for ( i = 1 ; i < 14 ; i ++ )
		fprintf ( out , " %s" , pex_order[i] ) ;
	fprintf ( out , " %s" , pex_order[0] ) ;
	fprintf ( out , "\n\n" ) ;

	// generage input vectors
	fprintf ( out , "VVDD VDD 0 %.1lf\n" , VDD ) ;
	fprintf ( out , "VGND GND 0 %.1lf\n" , 0.0 ) ;
	gen_vec ( out , "A0SRC" , A0 , pattern_number , period ) ;
	gen_tg  ( out , "A0SRC" , "A0" ) ;
	gen_vec ( out , "A1SRC" , A1 , pattern_number , period ) ;
	gen_tg  ( out , "A1SRC" , "A1" ) ;
	gen_vec ( out , "A2SRC" , A2 , pattern_number , period ) ;
	gen_tg  ( out , "A2SRC" , "A2" ) ;
	gen_vec ( out , "B0SRC" , B0 , pattern_number , period ) ;
	gen_tg  ( out , "B0SRC" , "B0" ) ;
	gen_vec ( out , "B1SRC" , B1 , pattern_number , period ) ;
	gen_tg  ( out , "B1SRC" , "B1" ) ;
	gen_vec ( out , "B2SRC" , B2 , pattern_number , period ) ;
	gen_tg  ( out , "B2SRC" , "B2" ) ;
	gen_vec ( out , "CINSRC" , CIN , pattern_number , period ) ;
	gen_tg  ( out , "CINSRC" , "CIN" ) ;
	gen_vec ( out , "AS0" , AS0 , pattern_number , period ) ;
	gen_vec ( out , "AS1" , AS1 , pattern_number , period ) ;
	gen_vec ( out , "AS2" , AS2 , pattern_number , period ) ;
	gen_vec ( out , "ACOUT" , ACOUT , pattern_number , period ) ;
	fprintf ( out , "CS0 S0 0 %.2lff\n" , LOAD ) ;
	fprintf ( out , "CS1 S1 0 %.2lff\n" , LOAD ) ;
	fprintf ( out , "CS2 S2 0 %.2lff\n" , LOAD ) ;
	fprintf ( out , "CCOUT COUT 0 %.2lff\n" , LOAD ) ;
	
	fprintf ( out , "\n\n" ) ;

	// simulation and analysis
	fprintf ( out , ".OPTIONS LIST NODE POST\n" ) ;
	fprintf ( out , ".TRAN 5P %.0lfN\n" , max_sim_time+2.0 ) ;

	fprintf ( out , ".PRINT V(A0) V(A1) V(A2) V(B0) V(B1) V(B2) V(CIN) V(S0) V(S1) V(S2) V(COUT)\n" ) ;
	fprintf ( out , ".PROB V(A0) V(A1) V(A2) V(B0) V(B1) V(B2) V(CIN) V(S0) V(S1) V(S2) V(COUT) V(AS0) V(AS1) V(AS2) V(ACOUT)\n" ) ;
	fprintf ( out , ".END\n\n" ) ;

	// close file
	fclose ( pex ) ;
	fclose ( out ) ;

	printf ( "Done.\n%s generated successfully.\n" , argc[1] ) ;


	if ( patch_pex_file ) {
		system ( "mv ADDER3.pex.netlist _bk_ADDER3.pex.netlist" ) ;
		system ( "cat _bk_ADDER3.pex.netlist | sed 's/\\([a-zA-Z]\\)\\.\\([a-zA-Z0-9]\\)/\\1_\\2/g' | sed 's/\\([a-zA-Z0-9]\\)\\.\\([a-zA-Z]\\)/\\1_\\2/g' | sed 's/ADDER3_pex_netlist_ADDER3_pxi/ADDER3.pex.netlist.ADDER3.pxi/g' | sed 's/ADDER3_pex_netlist_pex/ADDER3.pex.netlist.pex/g' >> ADDER3.pex.netlist" ) ;

		system ( "mv ADDER3.pex.netlist.ADDER3.pxi _bk_ADDER3.pex.netlist.ADDER3.pxi" ) ;
		system ( "cat _bk_ADDER3.pex.netlist.ADDER3.pxi | sed 's/\\([a-zA-Z]\\)\\.\\([a-zA-Z0-9]\\)/\\1_\\2/g' | sed 's/\\([a-zA-Z0-9]\\)\\.\\([a-zA-Z]\\)/\\1_\\2/g' | sed 's/ADDER3_pex_netlist_ADDER3_pxi/ADDER3.pex.netlist.ADDER3.pxi/g' | sed 's/ADDER3_pex_netlist_pex/ADDER3.pex.netlist.pex/g' >> ADDER3.pex.netlist.ADDER3.pxi" ) ;

		system ( "mv ADDER3.pex.netlist.pex _bk_ADDER3.pex.netlist.pex" ) ;
		system ( "cat _bk_ADDER3.pex.netlist.pex | sed 's/\\([a-zA-Z]\\)\\.\\([a-zA-Z0-9]\\)/\\1_\\2/g' | sed 's/\\([a-zA-Z0-9]\\)\\.\\([a-zA-Z]\\)/\\1_\\2/g' | sed 's/ADDER3_pex_netlist_ADDER3_pxi/ADDER3.pex.netlist.ADDER3.pxi/g' | sed 's/ADDER3_pex_netlist_pex/ADDER3.pex.netlist.pex/g' >> ADDER3.pex.netlist.pex" ) ;
		printf ( "Finish update pex files.\n" ) ;
	}

	return 0 ;
}

void gen_vec ( FILE * out , char * name , int val[] , int len , double period ) {
	int i ;
	double t ;
	double dt = 0.0005 ;
	t = 0 ;
	fprintf ( out , "V%s %s 0 PWL ( %.4lfn %.1lf " , name , name , t , val[0]==1?VDD:0 ) ;
	for ( i = 0 ; i < len ; i ++ ) {
		fprintf ( out , " , %.4lfn %.1lf , %.4lfn %.1lf " , t+dt , val[i]==1?VDD:0 , t+period-dt , val[i]==1?VDD:0 ) ;
		t = t+period ;
	}
	fprintf ( out , ")\n" ) ;
	if ( max_sim_time < t ) max_sim_time = t ;
}

int check ( char * item ) {
	if ( !strcmp("ADDER3", item) ) return 1 ;
	if ( !strcmp("A0", item) ) return 1 ;
	if ( !strcmp("A1", item) ) return 1 ;
	if ( !strcmp("A2", item) ) return 1 ;
	if ( !strcmp("B0", item) ) return 1 ;
	if ( !strcmp("B1", item) ) return 1 ;
	if ( !strcmp("B2", item) ) return 1 ;
	if ( !strcmp("CIN", item) ) return 1 ;
	if ( !strcmp("S0", item) ) return 1 ;
	if ( !strcmp("S1", item) ) return 1 ;
	if ( !strcmp("S2", item) ) return 1 ;
	if ( !strcmp("COUT", item) ) return 1 ;
	if ( !strcmp("VDD", item) ) return 1 ;
	if ( !strcmp("GND", item) ) return 1 ;
	return 0 ;
}

void gen_tg ( FILE * out , char * in_name , char * out_name ) {

	fprintf ( out , "m_%s_in_TG_mn1 %s VDD %s GND N_18 L=1.8e-07 W=6.7e-07\n" ,
		out_name , out_name , in_name ) ;
	fprintf ( out , "+ AD=7.169e-13 AS=6.432e-13 PD=2.81e-06 PS=2.59e-06\n" ) ;

	fprintf ( out , "m_%s_in_TG_mp1 %s GND %s VDD P_18 L=1.8e-07 W=6.7e-07\n" ,
		out_name , out_name , in_name ) ;
	fprintf ( out , "+ AD=7.169e-13 AS=6.432e-13 PD=2.81e-06 PS=2.59e-06\n" );
}


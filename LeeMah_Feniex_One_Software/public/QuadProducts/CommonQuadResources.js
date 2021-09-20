const OFF =0x00;
const ALL = 0x03;

const BLUE = 0x03;
const RED = 0x0C;
const AMBER = 0x30;
const WHITE = 0xC0;

const FIFTY_PERCENT_BRIGHT = 0xAA;
const TEN_PERCENT_BRIGHT = 0x55;

const END = 99;

const ClusterMix = [];

const HalfHalfSingle = [
        [ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF,			//Half-Half Fast and Slow
    ALL,										  	    OFF,
ALL,										  		        OFF,
    ALL,						  		  		        OFF,
        ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL,			//Half-Half Fast and Slow
    OFF,										  	    ALL,
OFF,										  			    ALL,
    OFF,						  		  		  	    ALL,
        OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL] ,
        [END]
];

const OneOneSingle = [
        [ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,			//One-One Fast and Slow
    OFF,										  	    ALL,
ALL,										  		        OFF,
    OFF,						  		  		        ALL,
        ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF],

        [OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,			//One-One Fast and Slow
    ALL,										  	    OFF,
OFF,										  			    ALL,
    ALL,						  		  		  	    OFF,
        OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL] ,
        [END]
];

const TwoTwoSingle = [
        [OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,			//Two Two and Slow
    OFF,										  	    OFF,
OFF,										  		        OFF,
    ALL,						  		  		        ALL,
        ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL],
        [ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,			//Two Two Fast and Slow
    ALL,										  	    ALL,
ALL,										  			    ALL,
    OFF,						  		  		  	    OFF,
        OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF] ,
        [END]
];

const AllOnSingle = [
        [ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,			//Two Two and Slow
    ALL,										  	    ALL,
ALL,										  		        ALL,
    ALL,						  		  		        ALL,
        ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,			//Two Two Fast and Slow
    OFF,										  	    OFF,
OFF,										  			    OFF,
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [END]
];

const HalfHalfTriple = [
        [ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF,			//Half-Half Fast and Slow
    ALL,										  	    OFF,
ALL,										  		        OFF,
    ALL,						  		  		        OFF,
        ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,			//Half-Half Fast and Slow
    OFF,										  	    OFF,
OFF,										  		        OFF,
    OFF,						  		  		        OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],        
        [ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF,			//Half-Half Fast and Slow
    ALL,										  	    OFF,
ALL,										  		        OFF,
    ALL,						  		  		        OFF,
        ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,			//Half-Half Fast and Slow
    OFF,										  	    OFF,
OFF,										  		        OFF,
    OFF,						  		  		        OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF,			//Half-Half Fast and Slow
    ALL,										  	    OFF,
ALL,										  		        OFF,
    ALL,						  		  		        OFF,
        ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL,			//Half-Half Fast and Slow
    OFF,										  	    ALL,
OFF,										  			    ALL,
    OFF,						  		  		  	    ALL,
        OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,			//Half-Half Fast and Slow
    OFF,										  	    OFF,
OFF,										  		        OFF,
    OFF,						  		  		        OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF], 
        [OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL,			//Half-Half Fast and Slow
    OFF,										  	    ALL,
OFF,										  			    ALL,
    OFF,						  		  		  	    ALL,
        OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,			//Half-Half Fast and Slow
    OFF,										  	    OFF,
OFF,										  		        OFF,
    OFF,						  		  		        OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF], 
        [OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL,			//Half-Half Fast and Slow
    OFF,										  	    ALL,
OFF,										  			    ALL,
    OFF,						  		  		  	    ALL,
        OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL],
        [END]
];

const ComboTriple = [
        [OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL,			//Half-Half Fast and Slow
    OFF,										  	    ALL,
OFF,										  			    ALL,
    OFF,						  		  		  	    ALL,
        OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,			//All On Fast and Slow
    OFF,										  	    OFF,
OFF,										  			    OFF,
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF,			//Half-Half Fast and Slow
    ALL,										  	    OFF,
ALL,										  		        OFF,
    ALL,						  		  		        OFF,
        ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF],
        [END]
];

const OneOneTriple = [
        [ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,			//One-One Fast and Slow
    OFF,										  	    ALL,
ALL,										  		        OFF,
    OFF,						  		  		        ALL,
        ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,			//One-One Fast and Slow
    OFF,										  	    OFF,
OFF,										  		        OFF,
    OFF,						  		  		        OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,			//One-One Fast and Slow
    OFF,										  	    ALL,
ALL,										  		        OFF,
    OFF,						  		  		        ALL,
        ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,			//One-One Fast and Slow
    OFF,										  	    OFF,
OFF,										  		        OFF,
    OFF,						  		  		        OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,			//One-One Fast and Slow
    OFF,										  	    ALL,
ALL,										  		        OFF,
    OFF,						  		  		        ALL,
        ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF],
        [OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,			//One-One Fast and Slow
    ALL,										  	    OFF,
OFF,										  			    ALL,
    ALL,						  		  		  	    OFF,
        OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,			//One-One Fast and Slow
    OFF,										  	    OFF,
OFF,										  		        OFF,
    OFF,						  		  		        OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],   
        [OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,			//One-One Fast and Slow
    ALL,										  	    OFF,
OFF,										  			    ALL,
    ALL,						  		  		  	    OFF,
        OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,			//One-One Fast and Slow
    OFF,										  	    OFF,
OFF,										  		        OFF,
    OFF,						  		  		        OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],   
        [OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,			//One-One Fast and Slow
    ALL,										  	    OFF,
OFF,										  			    ALL,
    ALL,						  		  		  	    OFF,
        OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL],  
        [END]   
];

const TwoTwoTriple = [
        [OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,			//Two Two and Slow
    OFF,										  	    OFF,
OFF,										  		        OFF,
    ALL,						  		  		        ALL,
        ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,			//One-One Fast and Slow
    OFF,										  	    OFF,
OFF,										  		        OFF,
    OFF,						  		  		        OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF], 
        [OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,			//Two Two and Slow
    OFF,										  	    OFF,
OFF,										  		        OFF,
    ALL,						  		  		        ALL,
        ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,			//One-One Fast and Slow
    OFF,										  	    OFF,
OFF,										  		        OFF,
    OFF,						  		  		        OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],  
        [OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,			//Two Two and Slow
    OFF,										  	    OFF,
OFF,										  		        OFF,
    ALL,						  		  		        ALL,
        ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL],
        [ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,			//Two Two Fast and Slow
    ALL,										  	    ALL,
ALL,										  			    ALL,
    OFF,						  		  		  	    OFF,
        OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,			//One-One Fast and Slow
    OFF,										  	    OFF,
OFF,										  		        OFF,
    OFF,						  		  		        OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],   
        [ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,			//Two Two Fast and Slow
    ALL,										  	    ALL,
ALL,										  			    ALL,
    OFF,						  		  		  	    OFF,
        OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,			//One-One Fast and Slow
    OFF,										  	    OFF,
OFF,										  		        OFF,
    OFF,						  		  		        OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF], 
        [ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,			//Two Two Fast and Slow
    ALL,										  	    ALL,
ALL,										  			    ALL,
    OFF,						  		  		  	    OFF,
        OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF],                  
        [END]   
];

const AllOnTriple = [
        [ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,
    ALL,										  	    ALL,
ALL,										  		        ALL,
    ALL,						  		  		        ALL,
        ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,
    ALL,										  	    ALL,
ALL,										  		        ALL,
    ALL,						  		  		        ALL,
        ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,
    ALL,										  	    ALL,
ALL,										  		        ALL,
    ALL,						  		  		        ALL,
        ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF] ,
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF] ,
        [END]
];

const Attack = [
        [ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,				//153
    ALL,                                                ALL,
ALL,                                                        ALL,
    ALL,                                                ALL,
        ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,				//154 		
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,				//155
    ALL,                                                ALL,
ALL,                                                        ALL,
    ALL,                                                ALL,
        ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,				//156 		
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,				//157 		
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL,				//158		
    OFF,                                                ALL,
OFF,                                                        ALL,
    OFF,                                                ALL,
        OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,				//159 		
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL,				//160		
    OFF,                                                ALL,
OFF,                                                        ALL,
    OFF,                                                ALL,
        OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,				//161 		
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF,				//162		
    ALL,                                                OFF,
ALL,                                                        OFF,
    ALL,                                                OFF,
        ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,				//163 		
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF,				//164		
    ALL,                                                OFF,
ALL,                                                        OFF,
    ALL,                                                OFF,
        ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,				//165
    ALL,                                                ALL,
ALL,                                                        ALL,
    ALL,                                                ALL,
        ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL],
        [OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,				//166		
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF],
        [ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,				//167
    ALL,                                                ALL,
ALL,                                                        ALL,
    ALL,                                                ALL,
        ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL],
        [OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,				//168		
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF],
        [ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,				//169
    ALL,                                                ALL,
ALL,                                                        ALL,
    ALL,                                                ALL,
        ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,				//170		 
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,				//171
    ALL,                                                ALL,
ALL,                                                        ALL,
    ALL,                                                ALL,
        ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,				//172		 
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,				//173		 
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,				//174
    ALL,                                                ALL,
ALL,                                                        ALL,
    ALL,                                                ALL,
        ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,				//175		 
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,				//176
    ALL,                                                ALL,
ALL,                                                        ALL,
    ALL,                                                ALL,
        ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL],
        [OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,				//177		
    ALL,                                                OFF,
OFF,                                                        ALL,
    ALL,                                                OFF,
        OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL],
        [ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,				//178
    OFF,                                                ALL,
ALL,                                                        OFF,
    OFF,                                                ALL,
        ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF],
        [OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,				//179		
    ALL,                                                OFF,
OFF,                                                        ALL,
    ALL,                                                OFF,
        OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL],
        [ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,				//180
    OFF,                                                ALL,
ALL,                                                        OFF,
    OFF,                                                ALL,
        ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,				//181		 
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,				//182
    ALL,                                                ALL,
ALL,                                                        ALL,
    ALL,                                                ALL,
        ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,				//183		 
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,				//184
    ALL,                                                ALL,
ALL,                                                        ALL,
    ALL,                                                ALL,
        ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL],
        [OFF,ALL,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,OFF,ALL,				//185
    OFF,                                                OFF,
OFF,                                                        ALL,
    ALL,                                                ALL,
        OFF,ALL,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,OFF,ALL],
        [OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,				//186		
    OFF,                                                ALL,
OFF,                                                        ALL,
    OFF,                                                ALL,
        OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL],
        [ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,				//187
    ALL,                                                OFF,
ALL,                                                        OFF,
    ALL,                                                OFF,
        ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF],
        [ALL,OFF,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,ALL,OFF,				//188		 
    ALL,                                                ALL,
ALL,                                                        OFF,
    OFF,                                                OFF,
        ALL,OFF,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,ALL,OFF],
        [ALL,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,OFF,				//189
    OFF,                                                ALL,
ALL,                                                        OFF,
    OFF,                                                OFF,
        ALL,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,OFF],
        [ALL,OFF,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,ALL,OFF,				//190		
    OFF,                                                ALL,
ALL,                                                        OFF,
    OFF,                                                OFF,
        ALL,OFF,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,ALL,OFF],
        [OFF,ALL,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,OFF,ALL,				//191
    ALL,                                                OFF,
OFF,                                                        ALL,
    ALL,                                                ALL,
        OFF,ALL,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,OFF,ALL],
        [OFF,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,ALL,				//192		
    ALL,                                                OFF,
OFF,                                                        ALL,
    ALL,                                                ALL,
        OFF,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,				//193		 
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,				//194
    ALL,                                                ALL,
ALL,                                                        ALL,
    ALL,                                                ALL,
        ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,				//195		 
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,				//196
    ALL,                                                ALL,
ALL,                                                        ALL,
    ALL,                                                ALL,
        ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL],
        [OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,				//197		
    ALL,                                                OFF,
OFF,                                                        ALL,
    ALL,                                                OFF,
        OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL],
        [ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,				//198
    OFF,                                                ALL,
ALL,                                                        OFF,
    OFF,                                                ALL,
        ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF],
        [OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,				//199		
    ALL,                                                OFF,
OFF,                                                        ALL,
    ALL,                                                OFF,
        OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL],
        [ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,				//200
    OFF,                                                ALL,
ALL,                                                        OFF,
    OFF,                                                ALL,
        ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF],
        [OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,				//201		
    ALL,                                                OFF,
OFF,                                                        ALL,
    ALL,                                                OFF,
        OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,				//202		 
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,				//203		
    ALL,                                                OFF,
OFF,                                                        ALL,
    ALL,                                                OFF,
        OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,				//204		 
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,				//205		
    OFF,                                                ALL,
ALL,                                                        OFF,
    OFF,                                                ALL,
        ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,				//206		 
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,				//207		
    OFF,                                                ALL,
ALL,                                                        OFF,
    OFF,                                                ALL,
        ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF,ALL,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,				//208		 
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,				//209
    ALL,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                ALL,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,				//210		
    ALL,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                ALL,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,ALL,				//211
    OFF,                                                OFF,
ALL,                                                        ALL,
    OFF,                                                OFF,
        ALL,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,ALL],
        [ALL,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,ALL,				//212		
    OFF,                                                OFF,
ALL,                                                        ALL,
    OFF,                                                OFF,
        ALL,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,ALL],
        [OFF,ALL,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,ALL,OFF,				//213
    OFF,                                                ALL,
OFF,                                                        OFF,
    ALL,                                                OFF,
        OFF,ALL,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,ALL,OFF],
        [OFF,ALL,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,ALL,OFF,				//214		
    OFF,                                                ALL,
OFF,                                                        OFF,
    ALL,                                                OFF,
        OFF,ALL,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,ALL,OFF],
        [OFF,OFF,ALL,OFF,OFF,OFF,OFF,OFF,OFF,ALL,OFF,OFF,				//215
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,ALL,OFF,OFF,OFF,OFF,OFF,OFF,ALL,OFF,OFF],
        [OFF,OFF,ALL,OFF,OFF,OFF,OFF,OFF,OFF,ALL,OFF,OFF,				//216		
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,ALL,OFF,OFF,OFF,OFF,OFF,OFF,ALL,OFF,OFF],
        [OFF,OFF,OFF,ALL,OFF,OFF,OFF,OFF,ALL,OFF,OFF,OFF,				//217
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,OFF,ALL,OFF,OFF,OFF,OFF,ALL,OFF,OFF,OFF],
        [OFF,OFF,OFF,ALL,OFF,OFF,OFF,OFF,ALL,OFF,OFF,OFF,				//218		
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,OFF,ALL,OFF,OFF,OFF,OFF,ALL,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,ALL,OFF,OFF,ALL,OFF,OFF,OFF,OFF,				//219
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,OFF,OFF,ALL,OFF,OFF,ALL,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,ALL,OFF,OFF,ALL,OFF,OFF,OFF,OFF,				//220		
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,OFF,OFF,ALL,OFF,OFF,ALL,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,ALL,ALL,OFF,OFF,OFF,OFF,OFF,				//221
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,OFF,OFF,OFF,ALL,ALL,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,ALL,ALL,OFF,OFF,OFF,OFF,OFF,				//222		
    OFF,                                                OFF,
OFF,                                                        OFF,
    OFF,                                                OFF,
        OFF,OFF,OFF,OFF,OFF,ALL,ALL,OFF,OFF,OFF,OFF,OFF]
];

const Cluster = [
        [OFF,ALL,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,OFF,ALL,
    ALL,                                             	OFF,
OFF,                                                    	ALL,		//105
    ALL,                                             	OFF,
        OFF,ALL,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,OFF,ALL],

        [ALL,OFF,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,ALL,OFF,
    OFF,												ALL,
ALL,														OFF,		//106
    OFF,												ALL,
        ALL,OFF,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,ALL,OFF],
        [OFF,ALL,ALL,OFF,OFF,OFF,ALL,ALL,ALL,OFF,OFF,ALL,
    ALL,                                                OFF,
OFF,                                                        ALL,		//107
    ALL,                                                OFF,
        OFF,ALL,ALL,OFF,OFF,OFF,ALL,ALL,ALL,OFF,OFF,ALL],
        [ALL,OFF,ALL,OFF,OFF,OFF,ALL,ALL,ALL,OFF,ALL,OFF,
    OFF,												ALL,
ALL,														OFF,		//108
    OFF,												ALL,
        ALL,OFF,ALL,OFF,OFF,OFF,ALL,ALL,ALL,OFF,ALL,OFF],
        [OFF,ALL,OFF,ALL,ALL,ALL,OFF,OFF,OFF,ALL,OFF,ALL,
    ALL,    											OFF,
OFF,    													ALL,		//109
    ALL,     											OFF,
        OFF,ALL,OFF,ALL,ALL,ALL,OFF,OFF,OFF,ALL,OFF,ALL],
        [ALL,OFF,OFF,ALL,ALL,ALL,OFF,OFF,OFF,ALL,ALL,OFF,
    OFF,												ALL,
ALL,														OFF,		//110
    OFF,												ALL,
        ALL,OFF,OFF,ALL,ALL,ALL,OFF,OFF,OFF,ALL,ALL,OFF],
        [OFF,ALL,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,OFF,ALL,
    ALL,        										OFF,
OFF,        												ALL,		//111
    ALL,        										OFF,
        OFF,ALL,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,OFF,ALL],
        [ALL,OFF,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,ALL,OFF,
    OFF,												ALL,
ALL,														OFF,		//112
    OFF,												ALL,
        ALL,OFF,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,ALL,OFF],
        [OFF,ALL,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,OFF,ALL,
    ALL,    											OFF,
OFF,    													ALL,		//113
    ALL,    											OFF,
        OFF,ALL,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,OFF,ALL],
        [ALL,OFF,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,ALL,OFF,
    OFF,												ALL,
ALL,														OFF,		//114
    OFF,												ALL,
        ALL,OFF,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,ALL,OFF],
        [OFF,ALL,ALL,OFF,OFF,OFF,ALL,ALL,ALL,OFF,OFF,ALL,
    ALL,    											OFF,
OFF,    													ALL,		//115
    ALL,    											OFF,
        OFF,ALL,ALL,OFF,OFF,OFF,ALL,ALL,ALL,OFF,OFF,ALL],
        [ALL,OFF,ALL,OFF,OFF,OFF,ALL,ALL,ALL,OFF,ALL,OFF,
    OFF,												ALL,
ALL,														OFF,		//116
    OFF,												ALL,
        ALL,OFF,ALL,OFF,OFF,OFF,ALL,ALL,ALL,OFF,ALL,OFF],
        [OFF,ALL,OFF,ALL,ALL,ALL,OFF,OFF,OFF,ALL,OFF,ALL,
    ALL,    											OFF,
OFF,    													ALL,		//117
    ALL,   												OFF,
        OFF,ALL,OFF,ALL,ALL,ALL,OFF,OFF,OFF,ALL,OFF,ALL],
        [ALL,OFF,OFF,ALL,ALL,ALL,OFF,OFF,OFF,ALL,ALL,OFF,
    OFF,												ALL,
ALL,														OFF,		//118
    OFF,												ALL,
        ALL,OFF,OFF,ALL,ALL,ALL,OFF,OFF,OFF,ALL,ALL,OFF],
        [OFF,ALL,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,OFF,ALL,
    ALL,    											OFF,
OFF,    													ALL,		//119
    ALL,   											 	OFF,
        OFF,ALL,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,OFF,ALL],
        [ALL,OFF,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,ALL,OFF,
    OFF,												ALL,
ALL,														OFF,		//120
    OFF,												ALL,
        ALL,OFF,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,ALL,OFF],
        [OFF,ALL,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,OFF,ALL,
    ALL,    											OFF,
OFF,   	 													ALL,		//121
    ALL,    											ALL,
        OFF,ALL,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,OFF,ALL],
        [OFF,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,ALL,
    ALL,												OFF,
OFF,														ALL,		//122
    ALL,												ALL,
        OFF,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,ALL],
        [ALL,OFF,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,ALL,OFF,
    OFF,    											ALL,
ALL,    													OFF,		//123
    OFF,    											OFF,
        ALL,OFF,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,ALL,OFF],
        [ALL,OFF,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,ALL,OFF,
    OFF,												ALL,
ALL,														OFF,		//124
    OFF,												OFF,
        ALL,OFF,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,ALL,OFF],
        [OFF,ALL,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,OFF,ALL,
    ALL,    											OFF,
OFF,    													ALL,		//125
    ALL,    											ALL,
        OFF,ALL,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,OFF,ALL],
        [OFF,ALL,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,OFF,ALL,
    ALL,    											ALL,
OFF,														ALL,		//126
    ALL,												ALL,
        OFF,ALL,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,OFF,ALL],
        [ALL,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,OFF,
    OFF,    											ALL,
ALL,    													OFF,		//127
    OFF,     											OFF,
        ALL,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,OFF],
        [ALL,OFF,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,ALL,OFF,
    OFF,												ALL,
ALL,														OFF,		//128
    OFF,												OFF,
        ALL,OFF,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,ALL,OFF],
        [OFF,ALL,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,OFF,ALL,
    ALL,    											OFF,
OFF,   													 	ALL,		//129
    ALL,    											ALL,
        OFF,ALL,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,OFF,ALL],
        [OFF,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,ALL,
    ALL,												OFF,
OFF,														ALL,		//130
    ALL,												ALL,
        OFF,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,ALL],
        [ALL,OFF,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,ALL,OFF,
    OFF,   	 											ALL,
ALL,    													OFF,		//131
    OFF,    											OFF,
        ALL,OFF,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,ALL,OFF],
        [ALL,OFF,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,ALL,OFF,
    OFF,												ALL,
ALL,														OFF,		//132
    OFF,												OFF,
        ALL,OFF,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,ALL,OFF],
        [OFF,ALL,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,OFF,ALL,
    ALL,    											OFF,
OFF,    													ALL,		//133
    ALL,     											ALL,
        OFF,ALL,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,OFF,ALL],
        [OFF,ALL,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,OFF,ALL,
    ALL,												OFF,
OFF,														ALL,		//134
    ALL,												ALL,
        OFF,ALL,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,OFF,ALL],
        [ALL,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,OFF,
    OFF,    											ALL,
ALL,   														OFF,		//135
    OFF,    											OFF,
        ALL,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,OFF],
        [ALL,OFF,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,ALL,OFF,
    OFF,												ALL,
ALL,														OFF,		//136
    OFF,												OFF,
        ALL,OFF,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,ALL,OFF],
        [OFF,ALL,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,OFF,ALL,
    OFF,            									OFF,
OFF,            											ALL,		//137
    ALL,            									ALL,
        OFF,ALL,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,OFF,ALL],
        [OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,
    OFF,												ALL,
OFF,														ALL,		//138
    OFF,												ALL,
        OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL],
        [OFF,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,ALL,
    OFF,   	 											OFF,
OFF,    													ALL,		//139
    ALL,    											ALL,
        OFF,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,ALL],
        [OFF,OFF,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,ALL,ALL,
    OFF,												ALL,
OFF,														ALL,		//140
    OFF,												ALL,
        OFF,OFF,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,ALL,ALL],
        [ALL,ALL,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,OFF,OFF,
    ALL,   												OFF,
ALL,    													OFF,		//141
    ALL,    											OFF,
        ALL,ALL,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,OFF,OFF],
        [ALL,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,OFF,
    ALL,												ALL,
ALL,														OFF,		//142
    OFF,												OFF,
        ALL,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,OFF],
        [ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,
    ALL,   	 											OFF,
ALL,    													OFF,		//143
    ALL,    											OFF,
        ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF],
        [ALL,OFF,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,ALL,OFF,
    ALL,												ALL,
ALL,														OFF,		//144
    OFF,												OFF,
        ALL,OFF,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,ALL,OFF],
        [OFF,ALL,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,OFF,ALL,
    OFF,    											OFF,
OFF,    													ALL,		//145
    ALL,    											ALL,
        OFF,ALL,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,OFF,ALL],
        [OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,
    OFF,												ALL,
OFF,														ALL,		//146
    OFF,												ALL,
        OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL],
        [OFF,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,ALL,
    OFF,    											OFF,
OFF,    													ALL,		//147
    ALL,    											ALL,
        OFF,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,ALL],
        [OFF,OFF,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,ALL,ALL,
    OFF,												ALL,
OFF,														ALL,		//148
    OFF,												ALL,
        OFF,OFF,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,ALL,ALL],
        [ALL,ALL,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,OFF,OFF,
    ALL,        						                OFF,
ALL,        							                    OFF,		//149
    ALL,        			       			            OFF,
        ALL,ALL,OFF,ALL,OFF,OFF,ALL,ALL,OFF,ALL,OFF,OFF],
        [ALL,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,OFF,
    ALL,							                    ALL,
ALL,								                        OFF,		//150
    OFF,							                    OFF,
        ALL,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,OFF],
        [ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,
    ALL,        						                OFF,
ALL,       	 						                        OFF,		//151
    ALL,        						                OFF,
        ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF,ALL,ALL,OFF,OFF],
        [ALL,OFF,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,ALL,OFF,
    ALL,							                    ALL,
ALL,								                        OFF,		//152
    OFF,							                    OFF,
        ALL,OFF,ALL,OFF,ALL,ALL,OFF,OFF,ALL,OFF,ALL,OFF]
];

const LeftPattern = [
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//72
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//73
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//74
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//75
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//76
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//77
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//78
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//79
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//80
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//81
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//82
    OFF,						  		  		  	    OFF,
        OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//83
    OFF,						  		  		  	    OFF,
        OFF,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//84
    OFF,						  		  		  	    OFF,
        ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL]
];

const RightPattern = [
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//85
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//86
    OFF,						  		  		  	    OFF,
        ALL,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//87
    OFF,						  		  		  	    OFF,
        ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//88
    OFF,						  		  		  	    OFF,
        ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//89
    OFF,						  		  		  	    OFF,
        ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//90
    OFF,						  		  		  	    OFF,
        ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//91
    OFF,						  		  		  	    OFF,
        ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//92
    OFF,						  		  		  	    OFF,
        ALL,ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//93
    OFF,						  		  		  	    OFF,
        ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//94
    OFF,						  		  		  	    OFF,
        ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//95
    OFF,						  		  		  	    OFF,
        ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//96
    OFF,						  		  		  	    OFF,
        ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//97
    OFF,						  		  		  	    OFF,
        ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL]
];

const CenterPattern = [
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										    	OFF,
OFF,										  			    OFF,			//98
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//99
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,ALL,ALL,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//100
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//101
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//102
    OFF,						  		  		  	    OFF,
        OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//103
    OFF,						  		  		  	    OFF,
        OFF,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//104
    OFF,						  		  		  	    OFF,
        ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL]
];

const EndCorner = [
        [ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    ALL,        										OFF,
ALL,       	 												OFF,		    //223
    ALL,        										OFF,
        ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,
    OFF,        										ALL,
OFF,       	 												ALL,		    //224
    OFF,        										ALL,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL]
];

const standardOnBrake = [
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,        										OFF,
OFF,       	 										        OFF,
    ALL,        										ALL,
        ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL]
];

const standardOnTurnLeft = [
        [ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF,
    ALL,        										OFF,
ALL,       	 										        OFF,
    ALL,        										OFF,
        ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF]
];

const standardOnTurnRight = [
        [OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL,
    OFF,        										ALL,
OFF,       	 										        ALL,
    OFF,        										ALL,
        OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL]
];

const standardOnFlood = [
        [ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,
    ALL,        										ALL,
ALL,       	 										        ALL,
    ALL,        										ALL,
        ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL]
];

const brakePop = [
        [ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,
    ALL,        										ALL,
ALL,       	 										        ALL,
    ALL,        										ALL,
        ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,        										OFF,
OFF,       	 										        OFF,
    OFF,        										OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF]
];

const LeftPatternSm = [
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//72
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,ALL,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//73
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//74
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//75
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//76
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//77
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//78
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL,ALL,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//79
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//80
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//81
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//82
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//83
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//84
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF]
];

const RightPatternSm = [
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//85
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//86
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//87
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//88
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//89
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//90
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//91
    OFF,						  		  		  	    OFF,
        ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//92
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//93
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//94
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//95
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//96
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//97
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF]
];

const CenterPatternSm = [
        [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
    OFF,										    	OFF,
OFF,										  			    OFF,			//98
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,OFF,ALL,ALL,OFF,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//99
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//100
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//101
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//102
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [OFF,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,OFF,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//103
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF],
        [ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,ALL,
    OFF,										  	    OFF,
OFF,										  			    OFF,			//104
    OFF,						  		  		  	    OFF,
        OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF]
];

// const turnSignalLeft = [
//         [ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF,
//     ALL,        										OFF,
// ALL,       	 										        OFF,
//     ALL,        										OFF,
//         ALL,ALL,ALL,ALL,ALL,ALL,OFF,OFF,OFF,OFF,OFF,OFF],
//         [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
//     OFF,        										OFF,
// OFF,       	 										        OFF,
//     OFF,        										OFF,
//         OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF]
// ];

// const turnSignalRight = [
//         [OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL,
//     OFF,        										ALL,
// OFF,       	 										        ALL,
//     OFF,        										ALL,
//         OFF,OFF,OFF,OFF,OFF,OFF,ALL,ALL,ALL,ALL,ALL,ALL],
//         [OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
//     OFF,        										OFF,
// OFF,       	 										        OFF,
//     OFF,        										OFF,
//         OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF]
// ];

const comboOfFlashPatterns = [
    [
        Attack[0], Attack[1], Attack[0], Attack[1], Attack[2], Attack[3], Attack[2], Attack[3], Attack[4], Attack[5],
        Attack[4], Attack[5], Attack[6], Attack[7], Attack[6], Attack[7], Attack[8], Attack[9], Attack[8], Attack[9],
        Attack[10], Attack[11], Attack[10], Attack[11], Attack[12], Attack[13], Attack[14], Attack[15], Attack[16], Attack[17],
        Attack[18], Attack[19], Attack[20], Attack[21], Attack[20], Attack[21], Attack[22], Attack[23], Attack[22], Attack[23],
        Attack[24], Attack[25], Attack[24], Attack[25], Attack[26], Attack[27], Attack[26], Attack[27], Attack[28], Attack[29],
        Attack[28], Attack[29], Attack[30], Attack[31], Attack[30], Attack[31], Attack[32], Attack[33], Attack[32], Attack[33],
        Attack[34], Attack[35], Attack[34], Attack[35], Attack[36], Attack[37], Attack[36], Attack[37], Attack[38], Attack[39],
        Attack[38], Attack[39], Attack[40], Attack[41], Attack[40], Attack[41], Attack[42], Attack[43], Attack[42], Attack[43],
        Attack[44], Attack[45], Attack[44], Attack[45], Attack[46], Attack[47], Attack[46], Attack[47], Attack[46], Attack[47],
        Attack[48], Attack[49], Attack[48], Attack[49], Attack[48], Attack[49], Attack[50], Attack[51], Attack[50], Attack[51],
        Attack[50], Attack[51], Attack[52], Attack[53], Attack[52], Attack[53], Attack[52], Attack[53], Attack[54], Attack[55],
        Attack[54], Attack[55], Attack[54], Attack[55], Attack[56], Attack[57], Attack[58], Attack[59], Attack[60], Attack[61], 
        Attack[62], Attack[63], Attack[64], Attack[65], Attack[66], Attack[67], Attack[66], Attack[67], END],      //Attack
    [
        Cluster[0], Cluster[1], Cluster[2], Cluster[3], Cluster[4], Cluster[5], Cluster[6], Cluster[7], Cluster[8], Cluster[9],
        Cluster[10], Cluster[11], Cluster[12], Cluster[13], Cluster[14], Cluster[15], Cluster[16], Cluster[17], Cluster[18], Cluster[19],
        Cluster[20], Cluster[21], Cluster[22], Cluster[23], Cluster[24], Cluster[25], Cluster[26], Cluster[27], Cluster[28], Cluster[29],
        Cluster[30], Cluster[31], Cluster[32], Cluster[33], Cluster[34], Cluster[35], Cluster[36], Cluster[37], Cluster[38], Cluster[39],
        Cluster[40], Cluster[41], Cluster[42], Cluster[43], Cluster[44], Cluster[45], Cluster[46], Cluster[47], END
    ],     //Cluster
    [ClusterMix[0], ClusterMix[1],END],
    [
        HalfHalfSingle[0], HalfHalfSingle[1], HalfHalfSingle[0], HalfHalfSingle[1], OneOneSingle[0], OneOneSingle[1], OneOneSingle[0], OneOneSingle[1], 
        TwoTwoSingle[0], TwoTwoSingle[1], TwoTwoSingle[0], TwoTwoSingle[1], AllOnSingle[0], AllOnSingle[1], AllOnSingle[0], AllOnSingle[1], END
    ], //Combo Single
    // [ClusterMix[0], ClusterMix[1],END],
    [
        HalfHalfTriple[0], HalfHalfTriple[1], HalfHalfTriple[2], HalfHalfTriple[3],HalfHalfTriple[4],
        HalfHalfTriple[5], HalfHalfTriple[6], HalfHalfTriple[7], HalfHalfTriple[8], HalfHalfTriple[9],
        HalfHalfTriple[0], HalfHalfTriple[1], HalfHalfTriple[2], HalfHalfTriple[3],HalfHalfTriple[4],
        HalfHalfTriple[5], HalfHalfTriple[6], HalfHalfTriple[7], HalfHalfTriple[8], HalfHalfTriple[9],
        OneOneTriple[0], OneOneTriple[1], OneOneTriple[2], OneOneTriple[3], OneOneTriple[4],
        OneOneTriple[5], OneOneTriple[6], OneOneTriple[7], OneOneTriple[8], OneOneTriple[9], 
        OneOneTriple[0], OneOneTriple[1], OneOneTriple[2], OneOneTriple[3], OneOneTriple[4],
        OneOneTriple[5], OneOneTriple[6], OneOneTriple[7], OneOneTriple[8], OneOneTriple[9], 
        TwoTwoTriple[0], TwoTwoTriple[1], TwoTwoTriple[2], TwoTwoTriple[3],TwoTwoTriple[4],
        TwoTwoTriple[5], TwoTwoTriple[6], TwoTwoTriple[7], TwoTwoTriple[8], TwoTwoTriple[9],
        TwoTwoTriple[0], TwoTwoTriple[1], TwoTwoTriple[2], TwoTwoTriple[3],TwoTwoTriple[4],
        TwoTwoTriple[5], TwoTwoTriple[6], TwoTwoTriple[7], TwoTwoTriple[8], TwoTwoTriple[9],
        AllOnTriple[0], AllOnTriple[1], AllOnTriple[2], AllOnTriple[3],
        AllOnTriple[4], AllOnTriple[5], AllOnTriple[6],
        AllOnTriple[0], AllOnTriple[1], AllOnTriple[2], AllOnTriple[3],
        AllOnTriple[4], AllOnTriple[5], AllOnTriple[6], END
    ], //Combo Triple

    [HalfHalfTriple, OneOneTriple, TwoTwoTriple, AllOnTriple, END], //Combo Triple Park

    [HalfHalfSingle[0], HalfHalfSingle[1], END],

    [HalfHalfTriple[0], HalfHalfTriple[1], HalfHalfTriple[2], HalfHalfTriple[3], HalfHalfTriple[4], HalfHalfTriple[5], HalfHalfTriple[6], HalfHalfTriple[7], HalfHalfTriple[8], HalfHalfTriple[9], END],

    [OneOneSingle[0], OneOneSingle[1], END],

    [OneOneTriple[0], OneOneTriple[1], OneOneTriple[2], OneOneTriple[3], OneOneTriple[4], OneOneTriple[5], OneOneTriple[6], OneOneTriple[7], OneOneTriple[8], OneOneTriple[9], END],

    [TwoTwoSingle[0], TwoTwoSingle[1], END],

    [TwoTwoTriple[0], TwoTwoTriple[1], TwoTwoTriple[2], TwoTwoTriple[3], TwoTwoTriple[4], TwoTwoTriple[5], TwoTwoTriple[6], TwoTwoTriple[7], TwoTwoTriple[8], TwoTwoTriple[9], END],

    [AllOnSingle[0], AllOnSingle[1], END],

    [AllOnTriple[0], AllOnTriple[1], AllOnTriple[2], AllOnTriple[3], AllOnTriple[4], AllOnTriple[5], AllOnTriple[6], END],

    [EndCorner[0], EndCorner[1], END],

    [
        LeftPattern[0], LeftPattern[1], LeftPattern[2], LeftPattern[3], LeftPattern[4], LeftPattern[5], LeftPattern[6], LeftPattern[7], LeftPattern[8], LeftPattern[9],
        LeftPattern[10], LeftPattern[11], LeftPattern[12], END
    ],  //Left-Slow
    [
        LeftPattern[0], LeftPattern[1], LeftPattern[2], LeftPattern[3], LeftPattern[4], LeftPattern[5], LeftPattern[6], LeftPattern[7], LeftPattern[8], LeftPattern[9],
        LeftPattern[10], LeftPattern[11], LeftPattern[12], END
    ],  //Left-Fast
    [
        LeftPattern[0], LeftPattern[1], LeftPattern[2], LeftPattern[3], LeftPattern[4], LeftPattern[5], LeftPattern[6], LeftPattern[7], LeftPattern[8], LeftPattern[9],
        LeftPattern[10], LeftPattern[11], LeftPattern[12], LeftPattern[0], LeftPattern[1], LeftPattern[2], LeftPattern[3], LeftPattern[4], LeftPattern[5], LeftPattern[6], 
        LeftPattern[7], LeftPattern[8], LeftPattern[9], LeftPattern[10], LeftPattern[11], LeftPattern[12], END
    ],  //Left-Combo
    [
        RightPattern[0], RightPattern[1], RightPattern[2], RightPattern[3], RightPattern[4], RightPattern[5], RightPattern[6], RightPattern[7], RightPattern[8], RightPattern[9],
        RightPattern[10], RightPattern[11], RightPattern[12], END
    ],  //Right-Slow
    [
        RightPattern[0], RightPattern[1], RightPattern[2], RightPattern[3], RightPattern[4], RightPattern[5], RightPattern[6], RightPattern[7], RightPattern[8], RightPattern[9],
        RightPattern[10], RightPattern[11], RightPattern[12], END
    ],  //Right-Fast
    [
        RightPattern[0], RightPattern[1], RightPattern[2], RightPattern[3], RightPattern[4], RightPattern[5], RightPattern[6], RightPattern[7], RightPattern[8], RightPattern[9],
        RightPattern[10], RightPattern[11], RightPattern[12], RightPattern[0], RightPattern[1], RightPattern[2], RightPattern[3], RightPattern[4], RightPattern[5], RightPattern[6], 
        RightPattern[7], RightPattern[8], RightPattern[9], RightPattern[10], RightPattern[11], RightPattern[12], END
    ],  //Right-Combo
    [
        CenterPattern[0], CenterPattern[1], CenterPattern[2], CenterPattern[3], CenterPattern[4], CenterPattern[5], CenterPattern[6], END
    ],  //Center-Slow
    [
        CenterPattern[0], CenterPattern[1], CenterPattern[2], CenterPattern[3], CenterPattern[4], CenterPattern[5], CenterPattern[6], END
    ],  //Center-Fast
    [
        CenterPattern[0], CenterPattern[1], CenterPattern[2], CenterPattern[3], CenterPattern[4], CenterPattern[5], CenterPattern[6], CenterPattern[0], CenterPattern[1], CenterPattern[2],
        CenterPattern[3], CenterPattern[4], CenterPattern[5], CenterPattern[6], END
    ],  //Center-Combo
    [
        standardOnBrake[0], END //24
    ], //Standard On
    [
        standardOnTurnLeft[0], END
    ], //Standard On
    [
        standardOnTurnRight[0], END
    ], //Standard On
    [
        standardOnFlood[0], END
    ], //Standard On
    [
        brakePop[0], brakePop[1], brakePop[0], brakePop[1], brakePop[0], brakePop[1], brakePop[0], END
    ], //Brake pop
    [
        HalfHalfSingle[0], HalfHalfSingle[1], HalfHalfSingle[0], HalfHalfSingle[1], OneOneSingle[0], OneOneSingle[1], OneOneSingle[0], OneOneSingle[1], 
        TwoTwoSingle[0], TwoTwoSingle[1], TwoTwoSingle[0], TwoTwoSingle[1], AllOnSingle[0], AllOnSingle[1], AllOnSingle[0], AllOnSingle[1], END
    ], //Vehicle Park
    // SM DIRECTIONAL PATTERNS
    [
        LeftPatternSm[0], LeftPatternSm[1], LeftPatternSm[2], LeftPatternSm[3], LeftPatternSm[4], LeftPatternSm[5], LeftPatternSm[6], LeftPatternSm[7], LeftPatternSm[8], LeftPatternSm[9],
        LeftPatternSm[10], LeftPatternSm[11], LeftPatternSm[12], END
    ],  //Left-Slow
    [
        LeftPatternSm[0], LeftPatternSm[1], LeftPatternSm[2], LeftPatternSm[3], LeftPatternSm[4], LeftPatternSm[5], LeftPatternSm[6], LeftPatternSm[7], LeftPatternSm[8], LeftPatternSm[9],
        LeftPatternSm[10], LeftPatternSm[11], LeftPatternSm[12], END
    ],  //Left-Fast
    [
        LeftPatternSm[0], LeftPatternSm[1], LeftPatternSm[2], LeftPatternSm[3], LeftPatternSm[4], LeftPatternSm[5], LeftPatternSm[6], LeftPatternSm[7], LeftPatternSm[8], LeftPatternSm[9],
        LeftPatternSm[10], LeftPatternSm[11], LeftPatternSm[12], LeftPatternSm[0], LeftPatternSm[1], LeftPatternSm[2], LeftPatternSm[3], LeftPatternSm[4], LeftPatternSm[5], LeftPatternSm[6], 
        LeftPatternSm[7], LeftPatternSm[8], LeftPatternSm[9], LeftPatternSm[10], LeftPatternSm[11], LeftPatternSm[12], END
    ],  //Left-Combo
    [
        RightPatternSm[0], RightPatternSm[1], RightPatternSm[2], RightPatternSm[3], RightPatternSm[4], RightPatternSm[5], RightPatternSm[6], RightPatternSm[7], RightPatternSm[8], RightPatternSm[9],
        RightPatternSm[10], RightPatternSm[11], RightPatternSm[12], END
    ],  //Right-Slow
    [
        RightPatternSm[0], RightPatternSm[1], RightPatternSm[2], RightPatternSm[3], RightPatternSm[4], RightPatternSm[5], RightPatternSm[6], RightPatternSm[7], RightPatternSm[8], RightPatternSm[9],
        RightPatternSm[10], RightPatternSm[11], RightPatternSm[12], END
    ],  //Right-Fast
    [
        RightPatternSm[0], RightPatternSm[1], RightPatternSm[2], RightPatternSm[3], RightPatternSm[4], RightPatternSm[5], RightPatternSm[6], RightPatternSm[7], RightPatternSm[8], RightPatternSm[9],
        RightPatternSm[10], RightPatternSm[11], RightPatternSm[12], RightPatternSm[0], RightPatternSm[1], RightPatternSm[2], RightPatternSm[3], RightPatternSm[4], RightPatternSm[5], RightPatternSm[6], 
        RightPatternSm[7], RightPatternSm[8], RightPatternSm[9], RightPatternSm[10], RightPatternSm[11], RightPatternSm[12], END
    ],  //Right-Combo
    [
        CenterPatternSm[0], CenterPatternSm[1], CenterPatternSm[2], CenterPatternSm[3], CenterPatternSm[4], CenterPatternSm[5], CenterPatternSm[6], END
    ],  //Center-Slow
    [
        CenterPatternSm[0], CenterPatternSm[1], CenterPatternSm[2], CenterPatternSm[3], CenterPatternSm[4], CenterPatternSm[5], CenterPatternSm[6], END
    ],  //Center-Fast
    [
        CenterPatternSm[0], CenterPatternSm[1], CenterPatternSm[2], CenterPatternSm[3], CenterPatternSm[4], CenterPatternSm[5], CenterPatternSm[6], CenterPatternSm[0], CenterPatternSm[1], CenterPatternSm[2],
        CenterPatternSm[3], CenterPatternSm[4], CenterPatternSm[5], CenterPatternSm[6], END
    ],  //Center-Combo
    [
        standardOnFlood[0], END
    ], //Standard On

    // [
    //     turnSignalLeft[0], turnSignalLeft[1], END
    // ], //Turn Left
    // [
    //     turnSignalRight[0], turnSignalRight[1], END
    // ] //Turn Right
];  

const comboPatternTiming = [
    [
        13, 13, 13, 13, 13, 13, 13, 13, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
        5, 5, 5, 5, 13, 13, 13, 13, 13, 13, 13, 13, 5, 5, 5, 5, 5, 5, 5, 5, 
        13, 13, 13, 13, 13, 13, 13, 13, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 
        6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 
        13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, END
    ],         //Attack 442(13) + 96(6) + 320(5) + 14(1) = 8720 ms
    [
        6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
        6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
        6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
        6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
        6, 6, 6, 6, 6, 6, 6, 6, END
    ],        //Cluster 5280 ms
    [20, 20, 20, 20, END],        //Cluster Mix 800 ms
    [20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, END], //Combo Single 3200 ms
    [
        10, 8, 10, 8, 10, 10, 5, 10, 5, 10, 10, 8, 10, 8, 10,
        10, 5, 10, 5, 10, 10, 5, 10, 5, 10, 10, 5, 10, 5, 10, 10, 5, 10,
        5, 10, 10, 5, 10, 5, 10, 10, 5, 10, 5, 10, 10, 5, 10, 5, 10, 10, 5,
        10, 5, 10, 10, 5, 10, 5, 10, 10, 5, 10, 5, 10, 10, 10, 10, 5, 10, 5,
        10, 10, 10, END
    ], // 460(10) + 
    [20, 20, 20, 20, END], //Combo Triple Park 800 ms
    [10, 10, END],          //Half Half Single 200 ms
    [10, 8, 10, 8, 10, 10, 5, 10, 5, 10, END],          //Half Half Triple 860 ms
    [20, 20, END],          //One One Single 400 ms
    [10, 5, 10, 5, 10, 10, 5, 10, 5, 10, END],          //One One Triple 800 ms
    [20, 20, END],          //Two Two Single 400 ms
    [10, 5, 10, 5, 10, 10, 5, 10, 5, 10, END],         //Two Two Triple 800 ms
    [20, 20, END],          //All On Single 400 ms
    [10, 5, 10, 5, 10, 10, 10, END],          //All on Triple 600 ms
    [20, 20, END],          //End Corner 400 ms
    [30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, END],     //Left-Slow 3900 ms
    [10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, END],     //Left-Fast 1300 ms
    [30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, END],    //Left-Combo 5200 ms 
    [30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, END],     //Right-Slow 3900 ms pattern 18
    [10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, END],     //Right-Fast 1300 ms pattern 19
    [30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, END],    //Right-Combo 5200 ms pattern 20
    [30, 30, 30, 30, 30, 30, 30, END],   //Center-Slow 2100 ms pattern 21
    [10, 10, 10, 10, 10, 10, 10, END],   //Center-Fast 700 ms pattern 22
    [10, 10, 10, 10, 10, 10, 10, 30, 30, 30, 30, 30, 30, 30, END],    //Center-Combo 2800 ms pattern 23
    [0, END],         //Standard On
    [0, END],         //Standard On
    [0, END],         //Standard On
    [0, END],         //Standard On
    [7, 3, 6, 3, 6, 2, 0, END],        //Brake Pop 270 ms
    [20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, END],  //Vehicle Park 3200 ms
    [30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, END],     //Left-Slow 3900 ms
    [10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, END],     //Left-Fast 1300 ms
    [30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, END],    //Left-Combo 5200 ms 
    [30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, END],     //Right-Slow 3900 ms pattern 18
    [10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, END],     //Right-Fast 1300 ms pattern 19
    [30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, END],    //Right-Combo 5200 ms pattern 20
    [30, 30, 30, 30, 30, 30, 30, END],   //Center-Slow 2100 ms pattern 21
    [10, 10, 10, 10, 10, 10, 10, END],   //Center-Fast 700 ms pattern 22
    [10, 10, 10, 10, 10, 10, 10, 30, 30, 30, 30, 30, 30, 30, END],     //Center-Combo 2800 ms pattern 23
    [300, END]         //Standard On for demo pattern
    // [37.7, 37.7, END],         //Left Turn
    // [37.7, 37.7, END],         //Right Turn
    // [0]           //All On
];

exports.ALL = ALL;
exports.OFF = OFF;
exports.END = END;

exports.comboOfFlashPatterns = comboOfFlashPatterns;
exports.comboPatternTiming = comboPatternTiming;

exports.BLUE = BLUE;
exports.RED = RED;
exports.AMBER = AMBER;
exports.WHITE = WHITE;
exports.FIFTY_PERCENT_BRIGHT = FIFTY_PERCENT_BRIGHT;
exports.TEN_PERCENT_BRIGHT = TEN_PERCENT_BRIGHT;
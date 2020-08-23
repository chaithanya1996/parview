# Parview
Parquet file command line utility is used to view data in parquet file. The utility can convert the parquet file to csv files.

## Usage 

 The utility has **head** and **tail** options that are used to display lines on parquet tables from start and end of the file. The default no of files that the head or tail displays is 50. The no of files can be specified via argument.
 
 Following command converts file to csv file
 ```
 $ parview file.parquet
 ```

 ```
 $ parview file.parquet --head 1 
 
 OR
 
 $ parview file.parquet -h 1
 
--------------------------------------------------------------------------------------------------------------------------------------------------------
     registration_dttm|  id|first_name|last_name|              email|   gender|    ip_address|                 cc|     country|  birthdate|     salary|              
--------------------------------------------------------------------------------------------------------------------------------------------------------
   1454486129000000000|   1|   Amanda|   Jordan|   ajordan0@com.com|   Female|   1.197.201.2|   6759521864920116|   Indonesia|   3/8/1971|   49756.53|
 
 
 $ parview file.parquet -t 1 
 
 OR 
 
 parview file.parquet --tail 1
 --------------------------------------------------------------------------------------------------------------------------------------------------------
     registration_dttm|     id|first_name|last_name|                 email|   gender|      ip_address|                cc| country|birthdate|      salary|title|comments|
--------------------------------------------------------------------------------------------------------------------------------------------------------
   1454493138000000000|   1000|   Julie|   Meyer|   jmeyerrr@flavors.me|   Female|   217.1.147.132|   374288099198540|   China|   |   222561.13|   |   |

 ```
 
 ## Installation
 
 Currently the utility offers a static binary built for linux and Macos. Download the utility from Releases section.
 
 ## Build
 
 The project uses apache arrow project to read the parquet files. 
 
 ### Dependencies 
 
 - CMake >=3.16
 - Boost >=1.73
 - Apache Arrow >=1.0 

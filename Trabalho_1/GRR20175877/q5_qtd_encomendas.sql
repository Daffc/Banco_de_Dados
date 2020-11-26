select distinct(N_NAME), count(O_ORDERKEY) contador 
    from CUSTOMER 
        left outer join NATION on N_NATIONKEY = C_NATIONKEY 
        left outer join ORDERS on C_CUSTKEY = O_CUSTKEY 
    group by N_NAME 
    order by contador 
    desc;

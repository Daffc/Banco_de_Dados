select distinct(N_NAME), sum(L_QUANTITY) contador 
    from CUSTOMER 
        left outer join NATION on N_NATIONKEY = C_NATIONKEY 
        left outer join ORDERS on C_CUSTKEY = O_CUSTKEY 
        left outer join LINEITEM on O_ORDERKEY = L_ORDERKEY 
    group by N_NAME 
    having contador > 6200000  
    order by contador 
    desc;
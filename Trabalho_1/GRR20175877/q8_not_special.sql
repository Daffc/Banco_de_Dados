select count(C_CUSTKEY) 
    from CUSTOMER 
    where C_CUSTKEY not in (
        select C_CUSTKEY 
        from CUSTOMER 
        left join ORDERS on C_CUSTKEY = O_CUSTKEY 
        where O_COMMENT = 'special request'
    );
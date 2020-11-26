select C_MKTSEGMENT, count(C_CUSTKEY) 
    from CUSTOMER 
    group by C_MKTSEGMENT;

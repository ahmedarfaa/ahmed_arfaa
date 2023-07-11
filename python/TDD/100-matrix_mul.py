#!/usr/bin/python3

def matrix_mul(m_a, m_b):
    if m_a == [] or m_a ==[[]]:
        raise ValueError("m_a can't be empty")
    
    if m_b == [] or m_b ==[[]]:
        raise ValueError("m_b can't be empty")
    
    if not isinstance(m_a, list):
        raise TypeError("m_a should be alist")
    
    if not isinstance(m_b, list):
        raise TypeError("m_b should be alist")
    
    if not all (isinstance(raw, list) for raw in m_a):
        raise TypeError("m_a must be a list of lists")
    
    if not all (isinstance(raw, list) for raw in m_b):
        raise TypeError("m_b must be a list of lists")
    
    if not all (isinstance(ele, int) or isinstance(ele, float) for ele in [num for raw in m_b for num in raw]):
        raise TypeError("m_b should contain only integers or floats")
    
    if not all (isinstance(ele, int) or isinstance(ele, float) for ele in [num for raw in m_a for num in raw]):
        raise TypeError("m_a should contain only integers or floats")
    
    if not all(len(raw) == len(m_a[0]) for raw in m_a):
        raise TypeError("each row of m_a must should be of the same size")
    
    if not all(len(raw) == len(m_a[0]) for raw in m_b):
        raise TypeError("each row of m_b must should be of the same size")
    
    if len(m_a[0]) != len(m_b):
        raise ValueError("m_a and m_b can't be multiplied")

    new_matrix = []
    for i in range(len(m_a)):
        new_row = []
        for j in range(len(m_b[0])):
            prod = 0
            for k in range(len(m_b)):
                prod += m_a[i][k] * m_b[k][j]
            new_row.append(prod)
        new_matrix.append(new_row)
    return new_matrix
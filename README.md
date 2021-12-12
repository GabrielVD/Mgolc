# Mgolc
 
Compiler implementation for the Mgol language. Project by Dra. Deborah Fernandes, Universidade Federal de Goiás.

Mgol is a simple language used as the specification for this educational project. Mgolc is a source-to-source compiler that produces C code. Features SLR(1) parsing and error recovery with no dependencies.

## Usage
``mgolc [input]``

- ``input`` one or more source files.

Output files have ``.out`` appended to the filename (``input.txt`` will be compiled to ``input.txt.out``).

``/resources`` contains a sample source file.

## Mgol production rules

1. P' → P
2. P → inicio V A
3. V → varinicio LV
4. LV → D LV
5. LV → varfim;
6. D → TIPO L;
7. L → id vir L
8. L → id
9. TIPO → inteiro
10. TIPO → real
11. TIPO → literal
12. A → ES A
13. ES → leia id;
14. ES → escreva ARG;
15. ARG → lit
16. ARG → num
17. ARG → id
18. A → CMD A
19. CMD → id rcb LD;
20. LD → OPRD opm OPRD
21. LD → OPRD
22. OPRD → id
23. OPRD → num
24. A → COND A
25. COND → CAB CP
26. CAB → se (EXP_R) então
27. EXP_R → OPRD opr OPRD
28. CP → ES CP
29. CP → CMD CP
30. CP → COND CP
31. CP → fimse
32. A → R A
33. R  → repita (EXP_R) CP_R
34. CP_R → ES CP_R
35. CP_R → CMD CP_R
36. CP_R → COND CP_R
37. CP_R → fimrepita
38. A → fim

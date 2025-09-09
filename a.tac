LABEL main:
a = 5
b = 3
c = 2.500000
d = 66
arr[0] = 10
arr[1] = 20
arr[2] = 30
t0 = &a
ptr = t0
t1 = a + b
result = t1
t2 = result + 1
result = t2
t3 = result - b
result = t3
t4 = result * 2
result = t4
t5 = result / 3
result = t5
t6 = result % 3
result = t6
t7 = a + b
sum = t7
t8 = a - b
diff = t8
t9 = a * b
prod = t9
t10 = a / b
div_res = t10
t11 = a % b
mod_res = t11
t12 = -a
neg_a = t12
t13 = !a
not_a = t13
t14 = &a
t15 = (TYPE_UNKNOWN)t14
addr_a = t15
t16 = *ptr
deref_ptr = t16
t17 = a == b
eq = t17
t18 = a != b
ne = t18
t19 = a < b
lt = t19
t20 = a <= b
le = t20
t21 = a > b
gt = t21
t22 = a >= b
ge = t22
t23 = a > 0
t24 = b < 10
IF_FALSE t23 GOTO L0
IF_FALSE t24 GOTO L0
t26 = 1
GOTO L1
LABEL L0:
t26 = 0
LABEL L1:
logical_and = t26
t27 = a < 0
t28 = b > 10
IF t27 GOTO L2
IF t28 GOTO L2
t30 = 0
GOTO L3
LABEL L2:
t30 = 1
LABEL L3:
logical_or = t30
t31 = a > b
IF_FALSE t31 GOTO L4
PARAM "a is greater than b"
t32 = CALL print_message, 1
GOTO L5
LABEL L4:
t33 = a < b
IF_FALSE t33 GOTO L6
PARAM "a is less than b"
t34 = CALL print_message, 1
GOTO L7
LABEL L6:
PARAM "a is equal to b"
t35 = CALL print_message, 1
LABEL L7:
LABEL L5:
i = 0
LABEL L8:
t36 = i < 3
IF_FALSE t36 GOTO L9
PARAM "While loop iteration: %d\n"
PARAM i
t37 = CALL printf, 2
i = i + 1
GOTO L8
LABEL L9:
j = 0
LABEL L10:
PARAM "Do-while loop iteration: %d\n"
PARAM j
t39 = CALL printf, 2
j = j + 1
t41 = j < 2
IF t41 GOTO L10
LABEL L11:
k = 0
LABEL L12:
t42 = k < 2
IF_FALSE t42 GOTO L13
PARAM "For loop iteration: %d\n"
PARAM k
t43 = CALL printf, 2
LABEL L14:
k = k + 1
GOTO L12
LABEL L13:
PARAM a
PARAM b
t45 = CALL add, 2
sum_ab = t45
PARAM "Sum of a and b: %d\n"
PARAM sum_ab
t46 = CALL printf, 2
t47 = arr[0]
first_element = t47
arr[1] = 25
PARAM "Array element at index 1: %d\n"
t48 = arr[1]
PARAM t48
t49 = CALL printf, 2
p1.x = 100
p1.y = 200
PARAM "Point p1: (%d, %d)\n"
PARAM p1.x
PARAM p1.y
t50 = CALL printf, 3
data.i = 123
PARAM "Union data.i: %d\n"
PARAM data.i
t51 = CALL printf, 2
data.f = 45.669998
PARAM "Union data.f: %f\n"
PARAM data.f
t52 = CALL printf, 2
t53 = a > b
IF t53 GOTO L15
t54 = b
GOTO L16
LABEL L15:
t54 = a
LABEL L16:
max = t54
PARAM "Max of a and b: %d\n"
PARAM max
t55 = CALL printf, 2
t56 = (TYPE_UNKNOWN)a
float_a = t56
PARAM "Float a: %f\n"
PARAM float_a
t57 = CALL printf, 2
PARAM "End of main function.\n"
t58 = CALL printf, 1
RETURN 0
LABEL add:
t59 = a + b
RETURN t59
LABEL print_message:
PARAM "%s\n"
PARAM msg
t60 = CALL printf, 2

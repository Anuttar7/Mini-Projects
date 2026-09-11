import numpy as np
import matplotlib.pyplot as plt
import sympy as sp
import sympy.tensor.array as spar

sp.init_printing(use_latex=True)

class Tensors:
    def __init__(self, x, u, x_expr, u_expr):
        self.x = x
        self.u = u
        self.x_expr = x_expr
        self.u_expr = u_expr
        
        self.g_ = [sp.simplify(sp.diff(x_expr, self.u[i])) for i in range(3)]
        self._g = [self.grad_x(self.u_expr[i]) for i in range(3)]
        self.g = [[sp.simplify(self.g_[i].dot(self.g_[j])) for j in range(3)] for i in range(3)]
        self.g_inv = [[sp.simplify(self._g[i].dot(self._g[j])) for j in range(3)] for i in range(3)]
        
        self.gamma1 = [[[sp.simplify(sp.diff(sp.Matrix(self.g_[i]), self.u[j]).dot(self.g_[k])) for k in range(3)] for j in range(3)] for i in range(3)]
        self.gamma2 = [[[sp.simplify(sp.diff(sp.Matrix(self.g_[i]), self.u[j]).dot(self._g[k])) for k in range(3)] for j in range(3)] for i in range(3)]

    def grad_x (self, f):
        return sp.Matrix([sp.simplify(sp.diff(f, self.x[i])) for i in range(3)])

    def covariant_basis (self):
        for i in range(3):    
            name = sp.symbols(r'g_{%s}' % str(i+1))
            eq = sp.Eq(name, sp.Matrix(self.g_[i]), evaluate=False)
            display(eq)
    
    def contravariant_basis (self):
        for i in range(3):    
            name = sp.symbols(r'g^{%s}' % str(i+1))
            eq = sp.Eq(name, sp.Matrix(self._g[i]).subs({self.u_expr[i] : self.u[i] for i in range(3)}), evaluate=False)
            display(eq)
    
    def metric_tensor (self, inv=False):
        if (inv != False and inv != True):
            raise Exception("Invalid inv! inv is a boolean.")
        elif (inv == True):
            name = sp.symbols(r'[g^{ij}]')
            eq = sp.Eq(name, sp.Matrix(self.g_inv), evaluate=False)
            display(eq)
        else:
            name = sp.symbols(r'[g_{ij}]')
            eq = sp.Eq(name, sp.Matrix(self.g), evaluate=False)
            display(eq)
    
    def christoffel_symbols (self, kind=2):
        if kind == 1:
            for i in range(1,4):
                for j in range(1,4):
                    for k in range(1,4):
                        name = sp.symbols(r'\Gamma_{%s%s%s}' % (i, j, k))
                        eq = sp.Eq(name, self.gamma1[i-1][j-1][k-1])
                        display(eq)
        elif kind == 2:
            for i in range(1,4):
                for j in range(1,4):
                    for k in range(1,4):
                        name = sp.symbols(r'\Gamma^{%s}_{%s%s}' % (k, i, j))
                        eq = sp.Eq(name, self.gamma2[i-1][j-1][k-1].subs({self.u_expr[i]: self.u[i] for i in range(3)}))
                        display(eq)
        else:
            raise Exception("Invalid kind! Choose between 1 and 2 only.")

    
    def grad_vector_coeff (self, a = 0, basis="covariant"):
        if (a == 0):
            if basis == "covariant":
                name = sp.symbols('[a_{i}|_{j}]')
                a = [sp.symbols(r'a_{%s}' % i) for i in range(1,4)]
                da_du = np.array([[sp.Derivative(a[i], self.u[j]) for j in range(3)] for i in range(3)])
                prod = np.array([[sum([a[k] * self.gamma2[i][j][k] for k in range(3)]) for j in range(3)] for i in range(3)])
                a_bar = da_du - prod
            elif basis == "contravariant":
                name = sp.symbols('[a^{i}|_{j}]')
                a = [sp.symbols(r'a^{%s}' % i) for i in range(1,4)]
                da_du = np.array([[sp.Derivative(a[i], self.u[j]) for j in range(3)] for i in range(3)])
                prod = np.array([[sum([a[k] * self.gamma2[i][j][k] for k in range(3)]) for j in range(3)] for i in range(3)])
                a_bar = da_du + prod
            else:
                raise Exception("Invalid basis! Choose between covariant and contravariant only.")
            
            eq = sp.Eq(name, sp.Matrix(a_bar).subs({self.u_expr[i] : self.u[i] for i in range(3)}), evaluate=False)
            display(eq)
        
        else:
            #Assuming covariant vector
            da_du = np.array([[sp.Derivative(a[i], self.u[j]).doit() for j in range(3)] for i in range(3)])
            prod = np.array([[sum([a[k] * self.gamma2[i][j][k] for k in range(3)]) for j in range(3)] for i in range(3)])
            a_bar = da_du - prod
            return sp.simplify(a_bar)

    #basis meaning:
    #1: T^{ij}
    #2: T_{ij}
    #3: T^{i}_{.j}
    def grad_tensor_coeff (self, T = 0, basis=1):
        if (T == 0):
            if basis == 1:
                T = [[sp.symbols(r'T^{%s%s}' % (i,j)) for j in range(1,4)] for i in range(1,4)]
                dT_du = np.array([[[sp.Derivative(T[i][j], self.u[k]) for k in range(3)] for j in range(3)] for i in range(3)])
                prod_i = np.array([[[sum([T[t][j] * self.gamma2[k][t][i] for t in range(3)]) for k in range(3)] for j in range(3)] for i in range(3)])
                prod_j = np.array([[[sum([T[i][t] * self.gamma2[k][t][j] for t in range(3)]) for k in range(3)] for j in range(3)] for i in range(3)])
                T_bar = dT_du + prod_i + prod_j
                [display(sp.Eq(sp.symbols(r'[T^{ij}|_{%s}]' % str(k)), sp.Matrix(T_bar[:][:][k]).subs({self.u_expr[i] : self.u[i] for i in range(3)}), evaluate=False)) for k in range(3)]
            elif basis == 2:
                T = [[sp.symbols(r'T_{%s%s}' % (i,j)) for j in range(1,4)] for i in range(1,4)]
                dT_du = np.array([[[sp.Derivative(T[i][j], self.u[k]) for k in range(3)] for j in range(3)] for i in range(3)])
                prod_i = np.array([[[sum([T[i][t] * self.gamma2[j][k][t] for t in range(3)]) for k in range(3)] for j in range(3)] for i in range(3)])
                prod_j = np.array([[[sum([T[j][t] * self.gamma2[i][k][t] for t in range(3)]) for k in range(3)] for j in range(3)] for i in range(3)])
                T_bar = dT_du - prod_i - prod_j
                [display(sp.Eq(sp.symbols(r'[T_{ij}|_{%s}]' % str(k)), sp.Matrix(T_bar[:][:][k]).subs({self.u_expr[i] : self.u[i] for i in range(3)}), evaluate=False)) for k in range(3)]
            elif basis == 3:
                T = [[sp.symbols(r'T^{%s}_{.%s}' % (i,j)) for j in range(1,4)] for i in range(1,4)]
                dT_du = np.array([[[sp.Derivative(T[i][j], self.u[k]) for k in range(3)] for j in range(3)] for i in range(3)])
                prod_i = np.array([[[sum([T[t][j] * self.gamma2[t][k][i] for t in range(3)]) for k in range(3)] for j in range(3)] for i in range(3)])
                prod_j = np.array([[[sum([T[i][t] * self.gamma2[j][k][t] for t in range(3)]) for k in range(3)] for j in range(3)] for i in range(3)])
                T_bar = dT_du + prod_i - prod_j
                [display(sp.Eq(sp.symbols(r'[T^{i}_{.j}|_{%s}]' % str(k)), sp.Matrix(T_bar[:][:][k]).subs({self.u_expr[i] : self.u[i] for i in range(3)}), evaluate=False)) for k in range(3)]
            else:
                raise Exception("Invalid basis! Choose between 1,2,3.")

        else:
            #Assuming T^{ij} as input
            T = [[sp.symbols(r'T^{%s%s}' % (i,j)) for j in range(1,4)] for i in range(1,4)]
            dT_du = np.array([[[sp.Derivative(T[i][j], self.u[k]) for k in range(3)] for j in range(3)] for i in range(3)])
            prod_i = np.array([[[sum([T[t][j] * self.gamma2[k][t][i] for t in range(3)]) for k in range(3)] for j in range(3)] for i in range(3)])
            prod_j = np.array([[[sum([T[i][t] * self.gamma2[k][t][j] for t in range(3)]) for k in range(3)] for j in range(3)] for i in range(3)])
            T_bar = dT_du + prod_i + prod_j
            return T_bar

    def div (self, T):
        if np.array(T).shape == (3,3):
            T_bar = self.grad_tensor_coeff(T)
            return [sum([sum([T_bar[i][k][k] for k in range(3)]) * self.g_[i][j] for i in range(3)]) for j in range(3)]
        elif np.array(T).shape == (3,):
            T_bar = self.grad_vector_coeff(T)
            return sp.simplify(sum([T_bar[i][i] for i in range(3)]))
        else:
            raise Exception("Only 1D or 2D Tensors are valid inputs.")
    
    def grad (self, T):
        if np.array(T).shape == (3,3):
            T_bar = self.grad_tensor_coeff(T)
            base = [[[spar.tensorproduct(list(np.squeeze(np.array(self.g_[i]))), spar.tensorproduct(list(np.squeeze(np.array(self.g_[j]))), list(np.squeeze(np.array(self._g[k]))))) for k in range(3)] for j in range(3)] for i in range(3)]
            return [[[sum([sum([sum([T_bar[i][j][k] * base[i][j][k][p][q][r] for k in range(3)]) for j in range(3)]) for i in range(3)]) for r in range(3)] for q in range(3)] for p in range(3)]
        elif np.array(T).shape == (3,):
            T_bar = self.grad_vector_coeff(T)
            base = [[spar.tensorproduct(list(np.squeeze(np.array(self.g_[i]))), list(np.squeeze(np.array(self._g[j])))) for j in range(3)] for i in range(3)]
            return [[sum([sum([T_bar[i][j] * base[i][j][p][q] for j in range(3)]) for i in range(3)]) for q in range(3)] for p in range(3)]
        else:
            raise Exception("Only 1D or 2D Tensors are valid inputs.")
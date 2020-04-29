package com.company;

public class Main {

    public static void main(String[] args) {
        double A[][] =  {
                { 5.3, 2.1, 2.8 },
                { 2.1, 4.7, 1.8 },
                { 2.7, 1.8, 6.1 }
        };
        double F[] = { 0.8, 5.7, 3.2 };

        double E = 0.001;
        double X[] = new double[A.length];
        for (int i = 0; i < A.length; i++) {
            X[i] = F[i] / A[i][i];
        }
        //итерации
        double max = E + 1;
        int k=0;
        double Xn[] = new double[X.length];
        while (max > E) {
            for (int i = 0; i < A.length; i++) {
                double sum1 = 0;
                for (int j = 0; j <= i - 1; j++) {
                    if (j != i)
                        sum1 -= A[i][j] * (Xn[j]) / A[i][i];
                }
                double sum2 = 0;
                for (int j = i; j < A.length; j++) {
                    if (j != i)
                        sum1 -= A[i][j] * (X[j]) / A[i][i];
                }
                Xn[i] = sum1 + sum2 + F[i] / A[i][i];
            }
            max = Math.abs(Xn[0] - X[0]);
            for (int i = 1; i < A.length; i++) {
                if (Math.abs(Xn[i] - X[i]) > max) {
                    max = Math.abs(Xn[i] - X[i]);
                }
            }
            if (max < E) {
                for (int i = 0; i < X.length; i++) {
                    System.out.println("X" + (i + 1) + ": " + Math.round(X[i] * 1000.0) / 1000.0);
                }
                System.out.println("Количество итераций: " +k);
                System.exit(1);
            }
            for (int i = 0; i < X.length; i++) {
                X[i] = Xn[i];
            }
            k++;
        }
    }
}

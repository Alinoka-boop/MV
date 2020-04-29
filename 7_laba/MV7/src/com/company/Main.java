package com.company;

public class Main {

    public static void main(String[] args) {
        double A[][] = {{-1.18, -0.34, -0.12, 0.15},
                {0.11, -0.77, -0.15, 0.32},
                {0.05, -0.12, -0.86, -0.18},
                {0.12, 0.08, 0.06, -1}};
        double F[] = {1.33, -0.84, 1.16, -0.57};
        double E = 0.00001;
        double X[] = new double[A.length];
        for (int i = 0; i < A.length; i++) {
            X[i] = F[i] / A[i][i];
        }
        int k = 0;
        double max = E + 1;
        double Xn[] = new double[X.length];
        while (max > E) {
            for (int i = 0; i < A.length; i++) {
                double sum = 0;
                for (int j = 0; j < A.length; j++) {
                    if (j != i) {
                        sum -= A[i][j] * (X[j]) / A[i][i];
                    }
                }
                Xn[i] = sum + F[i] / A[i][i];
            }

            //первая норма
            max = Math.abs(Xn[0] - X[0]);
            for (int i = 1; i < A.length; i++) {
                if (Math.abs(Xn[i] - X[i]) > max) {
                    max = Math.abs(Xn[i] - X[i]);
                }
            }
            System.out.println("Итерация " + k);
            for (int i = 0; i < X.length; i++) {
                System.out.println("X" + (i + 1) + ": " + Math.round(X[i] * 1000.0) / 1000.0);
            }
            System.out.println();

            if (max < E) {
                System.out.println("Ответ: ");
                for (int i = 0; i < X.length; i++) {
                    System.out.println("X" + (i + 1) + ": " + Math.round(X[i] * 1000.0) / 1000.0);
                }
                System.exit(1);
            }

            for (int i = 0; i < X.length; i++) {
                X[i] = Xn[i];
            }
            k++;
        }

    }
}

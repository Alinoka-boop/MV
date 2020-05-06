package com.company;

public class Main {
    public static void main(String[] args) {
        int N;
        double mass[][];
        N=3;
        mass=new double[N][N];

        mass[0][0]=2.2;  mass[0][1]=1;  mass[0][2]=1.2;
        mass[1][0]=1;  mass[1][1]=2.7;  mass[1][2]=1.2;
        mass[2][0]=1.2;  mass[2][1]=1.2;  mass[2][2]=3.2;
        int k=0;
        int n = N;
        double E = 0.001;
        double x;
        double xn = 1;
        double[] vec = new double[n];
        for (int i = 0; i < n; i++) {
            vec[i]=1;
        }
        double[] temp = new double[n];
        double[] max = new double[n];
        do {
            x = xn;
            for (int i = 0; i < n; i++) {
                temp[i]=0;
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    temp[i]=temp[i] + mass[i][j] * vec[j];
                }
            }
            xn = temp[0] / vec[0];
           System.out.println(Math.round(xn * 1000.0) / 1000.0);//закомментированно во втором случае
            for (int i = 0; i < n; i++)
            {
                vec[i]=temp[i];
            }
           /*for (int i = 0; i < n; i++)
                System.out.println(Math.round(vec[i] * 1000.0) / 1000.0);*///закомментированно в первом случае
        System.out.println();
            k++;

        } while(Math.abs(xn - x) > E);

        for (int i = 0; i < n; i++) {
            max[i]=vec[i] / vec[n - 1];
        }
        System.out.println("Итераций: " + k);
        System.out.println("max: "+ Math.round(xn * 100000.0) / 100000.0);
        System.out.println("vector:");
        for(int i=0;i<n;i++){
            System.out.println(Math.round(max[i] * 1000.0) / 1000.0);
        }
    }
}
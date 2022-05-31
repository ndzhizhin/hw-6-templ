#include <stdio.h>
#include <string.h>
#include <stdlib.h>

double f1(double x);
double f2(double x);
double f3(double x);

typedef double afunc(double);

double root(afunc *f, afunc *g, double a,double b,double eps1);
double integral(afunc *f, double a,double b,double eps2);

extern int count_iterations;//number of iterations to find the root
double eps1 = 0.0001;
double eps2 = 0.0001;

int main(int argc, char **argv) {
    if (argc == 1) { //calculate and display the area
        double x1 = root(f1, f3, -2.0, -1.5, eps1);
        double x2 = root(f2, f3, -1.0, 0, eps1);
        double x3 = root(f1, f2, 0, 1.0, eps1);
        double I1 = integral(f1,x1,x3,eps2);
        double I2 = integral(f2,x2,x3,eps2);
        double I3 = integral(f3,x1,x2,eps2);
        printf("I = %lf\n", I1 - I3 - I2);

    } else {
        if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) { //print all options
            printf("--help, -h\n");
            printf("--iterations, -i\n");
            printf("--test-root, -R\n");
            printf("--test-integral, -I\n");
        }

        if (strcmp(argv[1], "--root") == 0 || strcmp(argv[1], "-r") == 0) { //count all intersection points
            double root1 = root(f1, f2, 0, 1.0, eps1);
            printf("Root for functions f1 and f2 = %lf\n", root1);
            double root2 = root(f1, f3, -2.0, -1.5, eps1);
            printf("Root for functions f1 and f3 = %lf\n", root2);
            double root3 = root(f2, f3, -1.0, 0, eps1);
            printf("Root for functions f2 and f3 = %lf\n", root3);
        }

        if (strcmp(argv[1], "--iterations") == 0 || strcmp(argv[1], "-i") == 0) {//print amount of iterations to find each root
            double root1 = root(f1, f2, 0, 1.0, eps1);
            printf("Amount of iterations for functions f1 and f2 :%d\n", count_iterations);
            count_iterations = 0;

            double root2 = root(f1, f3, -2.0, -1.5, eps1);
            printf("Amount of iterations for functions f1 and f3 :%d\n", count_iterations);
            count_iterations = 0;

            double root3 = root(f2, f3, -1.0, 0, eps1);
            printf("Amount of iterations for functions f2 and f3 :%d\n", count_iterations);
            count_iterations = 0;
        }


        if ((strcmp(argv[1], "--test-root") == 0) || (strcmp(argv[1], "-R") == 0)) {//testing the function root
            char * oneParameter = strtok(argv[2], ":");
            int F1 = atoi(oneParameter);

            oneParameter = strtok(NULL, ":");
            int F2 = atoi(oneParameter);

            oneParameter = strtok(NULL, ":");
            double A = atof(oneParameter);

            oneParameter = strtok(NULL, ":");
            double B = atof(oneParameter);

            oneParameter = strtok(NULL, ":");
            double E = atof(oneParameter);

            oneParameter = strtok(NULL, ":");
            double R = atof(oneParameter);

            if (F1 == 1 && F2 == 2)
            {
                double checkRoot = root(f1, f2, A, B, E);
                printf("%lf %lf %lf\n",checkRoot,checkRoot - R,E / checkRoot);

            }

            else if (F1 == 2 && F2 == 3)
            {
                double checkRoot = root(f2, f3, A, B, E);
                printf("%lf %lf %lf\n",checkRoot,checkRoot - R,E / checkRoot);
            }
            else
            {
                double checkRoot = root(f1, f3, A, B, E);
                printf("%lf %lf %lf\n",checkRoot,checkRoot - R,E / checkRoot);
            }
        }

        if ((strcmp(argv[1], "--test-integral") == 0) || (strcmp(argv[1], "-I") == 0)) {//testing the function integral
            char * oneParameter = strtok(argv[2], ":");
            int F = atoi(oneParameter);

            oneParameter = strtok(NULL, ":");
            double A = atof(oneParameter);

            oneParameter = strtok(NULL, ":");
            double B = atof(oneParameter);

            oneParameter = strtok(NULL, ":");
            double E = atof(oneParameter);

            oneParameter = strtok(NULL, ":");
            double R = atof(oneParameter);

            if (F == 1) {
                double Sum = integral(f1, A, B, E);
                printf("%lf %lf %lf\n",Sum, Sum - R, E / Sum);
            }
            if (F == 2){
                double Sum = integral(f2, A, B, E);
                printf("%lf %lf %lf\n",Sum, Sum - R, E / Sum);
            }
            if (F == 3){
                double Sum = integral(f3, A, B, E);
                printf("%lf %lf %lf\n",Sum, Sum - R, E / Sum );
            }
        }
    }
    return 0;
}

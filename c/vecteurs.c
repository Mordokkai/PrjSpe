struct Vr{
	int dim;
	float* coeffs;
};

typedef struct Vr Vr;

struct VI{
	int dim;
	int* coef;
};

typedef struct VI VI;


Vr_alloue_special(int dim, int what) {
	Vr vr = (Vr) malloc(sizeof(Vr));
	vr->dim=dim;
	vr->coeffs=(float *) malloc(n*sizeof(float));
	return vr;
}

VI_alloue_special(int dim, int what){
	VI vi = (Vr) malloc(sizeof(Vr));
	vi->dim=dim;
	vi->coeffs=(int *) malloc(n*sizeof(int));
	return vi;
}

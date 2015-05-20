// x >
// y V

image integral_image(image i) {
	image ii;

	// Ligne 0
	ii(0,0) = i(0,0);	// Premi�re case
	for (i = 1; i < XMAX; i++) {
		ii(i,0) = i(i,0) + ii(i-1, 0);
	}

	// Lignes restantes
	for (j = 1; j < YMAX; j++) {
		ii(0,j) = i(0,j) + ii(0, j-1);	// Premi�re colonne
		for (i = 1; i < XMAX; i++) {
			ii(i,j) = i(i,j) + ii(i, j-1) + ii(i-1, j) - ii(i-1, j-1);
		}
	}

	return ii;
}
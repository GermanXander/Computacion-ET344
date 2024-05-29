/*
 * genera una archivo svg con el perfil de un ala NACA 6412
 * (National Advisory Committee for Aeronautics)
 * según se explica en:
 * http://airfoiltools.com/airfoil/naca4digit
 * 
 * Germán Andrés Xander 2023>
 */

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

int main(int argc, char **argv){
    ofstream salida ("ala.svg", ofstream::out | ofstream::trunc);      // creo objeto salida 

    if (salida.is_open()){
        salida << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>"<<endl<<endl;
        salida<< "<!-- Creado por Germán Andrés Xander 2022 con C++ -->"<<endl;
        salida<< "<svg"<<endl;
        salida<< "   width=\"297mm\""<<endl;
        salida<< "   height=\"210mm\""<<endl;
        salida<< "   viewBox=\"0 0 297mm 210mm\""<<endl;
        salida<< "   version=\"1.1\""<<endl;
        salida<< "   id=\"svg5\""<<endl;
        salida<< "   xmlns=\"http://www.w3.org/2000/svg\""<<endl;
        salida<< "   xmlns:svg=\"http://www.w3.org/2000/svg\">"<<endl;
        salida<< "  <defs"<<endl;
        salida<< "     id=\"defs2\" />"<<endl;
        salida<< "  <text"<<endl;
        salida<< "     xml:space=\"preserve\""<<endl;
        salida<< "     style=\"font-size:24px;line-height:1.25;font-family:sans-serif;text-align:start;text-anchor:start;stroke-width:0\""<<endl;
        salida<< "     x=\"10mm\""<<endl;
        salida<< "     y=\"20mm\""<<endl;
        salida<< "     id=\"text8850\"><tspan"<<endl;
        salida<< "       id=\"tspan8848\""<<endl;
        salida<< "       x=\"10mm\""<<endl;
        salida<< "       y=\"20mm\""<<endl;
        salida<< "       style=\"text-align:start;text-anchor:start;stroke-width:0\">Perfil Ala NACA 6412</tspan></text>"<<endl;
        salida<< "       <g id=\"layer1\">"<<endl;
        
        salida<< "  <path"<<endl;
        salida<< "     style=\"fill:none;stroke:#4d4d4d;stroke-width:0.755906;stroke-dasharray:none;stroke-opacity:1\""<<endl;
        salida<< "     d=\"m 151.77863,437.47765 0,-167.98431\""<<endl;
        salida<< "     id=\"ejey\""<<endl;
        salida<< "     sodipodi:nodetypes=\"cc\" />"<<endl;
        salida<< "  <path"<<endl;
        salida<< "     style=\"fill:none;stroke:#4d4d4d;stroke-width:0.755906;stroke-dasharray:none;stroke-opacity:1\""<<endl;
        salida<< "     d=\"m 132.07367,380.08571 821.05469,0\""<<endl;
        salida<< "     id=\"ejex\""<<endl;
        salida<< "     sodipodi:nodetypes=\"cc\" />"<<endl;

		int origenx = 4*38;
		int origeny = 10*38;
		int escala = 20*38;
				
        double beta = 0, yt, i = 0, x, yc = 0, tita, xu, yu, xl, yl, dyc, cxu, anteriorxu = origenx, cyu, anterioryu = origeny, cxl, anteriorxl = origenx, cyl, anterioryl = origeny, curvax, curvay;
        float P = 0.4;
        float M = 0.06;
        float T = 0.12;
        float a0 = 0.2969, a1 = -0.126, a2 = -0.3516, a3 = 0.2843, a4 = -0.1036;
        string envol_sup ("    d=\"m ");
        string envol_inf ("    d=\"m ");
        
        while (beta<=3.141592) {
			x = (1 - cos(beta))/2;
			yt = T * (a0*sqrt(x) + a1*x + a2*x*x + a3*x*x*x + a4*x*x*x*x) / 0.2;
			if (x < P){
				yc = (M/(P*P))*(2*P*x - x*x);
				dyc = (2*M/(P*P))*(P - x);
			} else {
				yc = (M/((1 - P) * (1 - P))) * (1 - 2*P + 2*P*x - x*x);
				dyc = (2*M/((1 - P) * (1 - P))) * (P - x);
			}
			tita = atan(dyc);
			anteriorxu = xu;
			anterioryu = yu;
			xu = escala*(x - yt * sin(tita)) + origenx;
			yu = origeny - escala*(yc + yt * cos(tita));

			anteriorxl = xl;
			anterioryl = yl;
			xl = escala*(x + yt * sin(tita)) + origenx;
			yl = origeny - escala*(yc - yt * cos(tita));

            salida<<endl<< "  <circle"<<endl;
            salida<< "    id=\"espesor"<<i<<"\""<<endl;
            salida<< "    style=\"fill:#00FF00;stroke:none;stroke-width:0\""<<endl;
            salida<< "    cx=\""<<escala*x + origenx<<"\""<<endl;
            salida<< "    cy=\""<<origeny - escala*yt<<"\""<<endl;   //positivo hacia abajo
            salida<< "    r=\"0.2mm\" />"<<endl;
            
            curvax = escala*x + origenx;
            curvay = origeny - escala*yc;
            
            salida<<endl<< "  <circle"<<endl;
            salida<< "    id=\"curvatura"<<i<<"\""<<endl;
            salida<< "    style=\"fill:#FF0000;stroke:none;stroke-width:0\""<<endl;
            salida<< "    cx=\""<<curvax<<"\""<<endl;
            salida<< "    cy=\""<<curvay<<"\""<<endl;   //positivo hacia abajo
            salida<< "    r=\"0.2mm\" />"<<endl;
            
            salida<<endl<< "  <circle"<<endl;
            salida<< "    id=\"envolvente_sup"<<i<<"\""<<endl;
            salida<< "    style=\"fill:#0000AA;stroke:none;stroke-width:0\""<<endl;
            salida<< "    cx=\""<<xu<<"\""<<endl;
            salida<< "    cy=\""<<yu<<"\""<<endl;   //positivo hacia abajo
            salida<< "    r=\"0.3mm\" />"<<endl;

            salida<<endl<< "  <circle"<<endl;
            salida<< "    id=\"envolvente_inf"<<i<<"\""<<endl;
            salida<< "    style=\"fill:#0000AA;stroke:none;stroke-width:0\""<<endl;
            salida<< "    cx=\""<<xl<<"\""<<endl;
            salida<< "    cy=\""<<yl<<"\""<<endl;   //positivo hacia abajo
            salida<< "    r=\"0.3mm\" />"<<endl;

			salida<<endl<< "  <path"<<endl;
			salida<< "    style=\"fill:none;stroke:#aaaaaa;stroke-width:0.02mm\""<<endl;
			salida<<"    d=\"m "<<curvax<<","<<curvay<<" "<<xu-curvax<<","<<yu-curvay<<"\""<<endl;
			salida<< "    id=\"perpendicularsup\""<<i<<endl;
			salida<< "    sodipodi:nodetypes=\"ccc\" />"<<endl;

            cxu = xu - anteriorxu;
            cyu = yu - anterioryu;
            
 			envol_sup.append(" ");
			envol_sup.append(to_string(cxu));
			envol_sup.append(",");
			envol_sup.append(to_string(cyu));
			
            cxl = xl - anteriorxl;
            cyl = yl - anterioryl;
            
 			envol_inf.append(" ");
			envol_inf.append(to_string(cxl));
			envol_inf.append(",");
			envol_inf.append(to_string(cyl));
			
            i++;
            beta += 0.03141592;
        }
        salida<< "</g>";
        
		salida<<endl<< "  <path"<<endl;
		salida<< "    style=\"fill:none;stroke:#0000ff;stroke-width:0.2mm\""<<endl;
		salida<<envol_sup<<"\""<<endl;
		salida<< "    id=\"curva_envolvente_sup\""<<endl;
		salida<< "    sodipodi:nodetypes=\"ccc\" />"<<endl;
					   
		salida<<endl<< "  <path"<<endl;
		salida<< "    style=\"fill:none;stroke:#0000ff;stroke-width:0.2\""<<endl;
		salida<<envol_inf<<"\""<<endl;
		salida<< "    id=\"curva_envolvente_inf\""<<endl;
		salida<< "    sodipodi:nodetypes=\"ccc\" />"<<endl;
					   
        salida<< "</svg>";

        salida.close();
    }
    else cout << "no se puede abrir el archivo"; 
    return 0;
}

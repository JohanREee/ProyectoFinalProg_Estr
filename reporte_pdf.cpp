#include "structs.h"
#include "complemento.cpp"

void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data)
{
    printf("ERROR: error_no=%04X, detail_no=%u\n", (unsigned int)error_no, (unsigned int)detail_no);
    exit(1);
}
void pdfReporteLotesPorRango()
{
    HPDF_Doc pdf_actual;
    HPDF_Font tipografia;
    HPDF_Page pagina;

    pdf_actual = HPDF_New(error_handler, NULL);
    if (!pdf_actual)
    {
        std::cout << "No se pudo crear el archivo pdf.\n";
        return;
    }
    pagina = HPDF_AddPage(pdf_actual);
    HPDF_Page_SetSize(pagina, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);


    HPDF_SaveToFile(pdf_actual, "Reporte_Lote_Por_Rango()");
    HPDF_Free(pdf_actual);
}

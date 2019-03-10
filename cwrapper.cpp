#include "tetgen.h" // Defined tetgenio, tetrahedralize().

typedef struct {
  int firstnumber; // 0 or 1, default 0.
  int mesh_dim;    // must be 3.

  double *pointlist;
  double *pointattributelist;
  double *pointmtrlist;
  int *pointmarkerlist;
  int numberofpoints;
  int numberofpointattributes;
  int numberofpointmtrs;

  int *tetrahedronlist;
  double *tetrahedronattributelist;
  double *tetrahedronvolumelist;
  int *neighborlist;
  int numberoftetrahedra;
  int numberofcorners;
  int numberoftetrahedronattributes;

  tetgenio::facet *facetlist;
  int *facetmarkerlist;
  int numberoffacets;

  double *holelist;
  int numberofholes;

  double *regionlist;
  int numberofregions;

  double *facetconstraintlist;
  int numberoffacetconstraints;

  double *segmentconstraintlist;
  int numberofsegmentconstraints;

  int *trifacelist;
  int *trifacemarkerlist;
  int numberoftrifaces;

  int *edgelist;
  int *edgemarkerlist;
  int numberofedges;
} TetGenIOf64;

void copy_tetio(tetgenio* in, TetGenIOf64* out){
    out->firstnumber = in->firstnumber;
    out->mesh_dim = in->mesh_dim;

    out->pointlist = in->pointlist;
    out->pointattributelist = in->pointattributelist;
    out->pointmtrlist = in->pointmtrlist;
    out->pointmarkerlist = in->pointmarkerlist;
    out->numberofpoints = in->numberofpoints;
    out->numberofpointattributes = in->numberofpointattributes;
    out->numberofpointmtrs = in->numberofpointmtrs;

    out->tetrahedronlist = in->tetrahedronlist;
    out->tetrahedronattributelist = in->tetrahedronattributelist;
    out->tetrahedronvolumelist = in->tetrahedronvolumelist;
    out->neighborlist = in->neighborlist;
    out->numberoftetrahedra = in->numberoftetrahedra;
    out->numberofcorners = in->numberofcorners;
    out->numberoftetrahedronattributes = in->numberoftetrahedronattributes;

    out->facetlist = in->facetlist;
    out->facetmarkerlist = in->facetmarkerlist;
    out->numberoffacets = in->numberoffacets;

    out->holelist = in->holelist;
    out->numberofholes = in->numberofholes;

    out->regionlist = in->regionlist;
    out->numberofregions = in->numberofregions;

    out->facetconstraintlist = in->facetconstraintlist;
    out->numberoffacetconstraints = in->numberoffacetconstraints;

    out->segmentconstraintlist = in->segmentconstraintlist;
    out->numberofsegmentconstraints = in->numberofsegmentconstraints;

    out->trifacelist = in->trifacelist;
    out->trifacemarkerlist = in->trifacemarkerlist;
    out->numberoftrifaces = in->numberoftrifaces;

    out->edgelist = in->edgelist;
    out->edgemarkerlist = in->edgemarkerlist;
    out->numberofedges = in->numberofedges;

}
void copy_tetio(TetGenIOf64* in, tetgenio* out){
    out->firstnumber = in->firstnumber;
    out->mesh_dim = in->mesh_dim;

    out->pointlist = in->pointlist;
    out->pointattributelist = in->pointattributelist;
    out->pointmtrlist = in->pointmtrlist;
    out->pointmarkerlist = in->pointmarkerlist;
    out->numberofpoints = in->numberofpoints;
    out->numberofpointattributes = in->numberofpointattributes;
    out->numberofpointmtrs = in->numberofpointmtrs;

    out->tetrahedronlist = in->tetrahedronlist;
    out->tetrahedronattributelist = in->tetrahedronattributelist;
    out->tetrahedronvolumelist = in->tetrahedronvolumelist;
    out->neighborlist = in->neighborlist;
    out->numberoftetrahedra = in->numberoftetrahedra;
    out->numberofcorners = in->numberofcorners;
    out->numberoftetrahedronattributes = in->numberoftetrahedronattributes;

    out->facetlist = in->facetlist;
    out->facetmarkerlist = in->facetmarkerlist;
    out->numberoffacets = in->numberoffacets;

    out->holelist = in->holelist;
    out->numberofholes = in->numberofholes;

    out->regionlist = in->regionlist;
    out->numberofregions = in->numberofregions;

    out->facetconstraintlist = in->facetconstraintlist;
    out->numberoffacetconstraints = in->numberoffacetconstraints;

    out->segmentconstraintlist = in->segmentconstraintlist;
    out->numberofsegmentconstraints = in->numberofsegmentconstraints;

    out->trifacelist = in->trifacelist;
    out->trifacemarkerlist = in->trifacemarkerlist;
    out->numberoftrifaces = in->numberoftrifaces;

    out->edgelist = in->edgelist;
    out->edgemarkerlist = in->edgemarkerlist;
    out->numberofedges = in->numberofedges;

}
extern "C" {

  TetGenIOf64 tetrahedralizef64(TetGenIOf64 jl_in, char* command){
    tetgenio in, out;
    copy_tetio(&jl_in, &in);
    tetrahedralize(command, &in, &out);
    TetGenIOf64 jl_out;
    copy_tetio(&out, &jl_out);
    in.initialize(); // don't free pointers from julia!
    out.initialize(); // don't free pointers for julia!
    return jl_out;
  }

}



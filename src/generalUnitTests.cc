#define BOOST_TEST_MODULE mopsGeneralUtilities

#include <boost/test/included/unit_test.hpp>
#include <boost/current_function.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <cmath>


#include "Detection.h"
#include "Exceptions.h"
#include "Tracklet.h"
#include "PointAndValue.h"
#include "common.h"
#include "KDTree.h"
#include "collapseTrackletsAndPostfilters/rmsLineFit.h"
#include "collapseTrackletsAndPostfilters/removeSubsets.h"


bool Eq(double a, double b) 
{
    double epsilon = 1e-10;
    return (fabs(a - b) < epsilon);
}











///////////////////////////////////////////////////////////////////////
//    DETECTION TESTS
///////////////////////////////////////////////////////////////////////



BOOST_AUTO_TEST_CASE( Detection_blackbox_1 )
{
    Detection myDet;
    long int ID = 10001;
    double MJD = 1234.5678;
    double RA = 2.02;
    double dec = 3.03;
    double obscode = 1337;
    std::string objName = "TestingObject1";
    double mag = 4.04;
    double len = 5.05;
    double angle = -6.06;
    std::stringstream ss("");
    ss << ID << " " << std::setprecision(12) << MJD << " " << RA << " " << dec << " " <<  mag << " "<< obscode
       << " " << objName << " " << len << " " << angle;

    std::string MITIString(ss.str());
    BOOST_CHECK(myDet.isInitialized() == false);
    myDet.fromMITIString(MITIString);
    BOOST_CHECK(myDet.isInitialized() == true);

    BOOST_CHECK (ID == myDet.getID() );    

    BOOST_CHECK (Eq(MJD, myDet.getEpochMJD())) ;
    BOOST_CHECK (Eq(RA,myDet.getRA()));
    BOOST_CHECK (Eq(dec,myDet.getDec())) ; 
    BOOST_CHECK (Eq(obscode,myDet.getObscode() ));
    BOOST_CHECK (objName == myDet.getObjName()); 
    BOOST_CHECK (Eq(mag,myDet.getMag()) ); 
    BOOST_CHECK (Eq(len,myDet.getLength())); 
    BOOST_CHECK (Eq(angle,myDet.getAngle()));
    BOOST_CHECK (myDet.hasExposureTime() == false);
}


BOOST_AUTO_TEST_CASE( Detection_blackbox_2 )
{
    //same as above, but with trailing whitespace
    Detection myDet;
    long int ID = 10001;
    double MJD = 1234.5678;
    double RA = 2.02;
    double dec = 3.03;
    double obscode = 1337;
    std::string objName = "TestingObject1";
    double mag = 4.04;
    double len = 5.05;
    double angle = -6.06;
    std::stringstream ss("");
    ss << ID << " "  << std::setprecision(12) << MJD << " " << RA << " " << dec << " " <<  mag << " "<< obscode
       << " " << objName << " " << len << " " << angle << "  ";

    std::string MITIString(ss.str());
    BOOST_CHECK(myDet.isInitialized() == false);
    myDet.fromMITIString(MITIString);
    BOOST_CHECK(myDet.isInitialized() == true);

    BOOST_CHECK (ID == myDet.getID() );
    BOOST_CHECK (Eq(MJD, myDet.getEpochMJD())) ;
    BOOST_CHECK (Eq(RA,myDet.getRA()));
    BOOST_CHECK (Eq(dec,myDet.getDec())) ; 
    BOOST_CHECK (Eq(obscode,myDet.getObscode() ));
    BOOST_CHECK (objName == myDet.getObjName()); 
    BOOST_CHECK (Eq(mag,myDet.getMag()) ); 
    BOOST_CHECK (Eq(len,myDet.getLength())); 
    BOOST_CHECK (Eq(angle,myDet.getAngle()));
    BOOST_CHECK (myDet.hasExposureTime() == false);
}


BOOST_AUTO_TEST_CASE( Detection_blackbox_3 )
{
    //same as 1, with whitespace in front
    Detection myDet;
    long int ID = 10001;
    double MJD = 1234.5678;
    double RA = 2.02;
    double dec = 3.03;
    double obscode = 1337;
    std::string objName = "TestingObject1";
    double mag = 4.04;
    double len = 5.05;
    double angle = -6.06;
    std::stringstream ss("");
    ss << " " << ID << " " << std::setprecision(12) << MJD << " " << RA << " " << dec << " " <<  mag << " "<< obscode
       << " " << objName << " " << len << " " << angle;

    std::string MITIString(ss.str());
    BOOST_CHECK(myDet.isInitialized() == false);
    myDet.fromMITIString(MITIString);
    BOOST_CHECK(myDet.isInitialized() == true);

    BOOST_CHECK (ID == myDet.getID() );
    BOOST_CHECK (Eq(MJD, myDet.getEpochMJD())) ;
    BOOST_CHECK (Eq(RA,myDet.getRA()));
    BOOST_CHECK (Eq(dec,myDet.getDec())) ; 
    BOOST_CHECK (Eq(obscode,myDet.getObscode() ));
    BOOST_CHECK (objName == myDet.getObjName()); 
    BOOST_CHECK (Eq(mag,myDet.getMag()) ); 
    BOOST_CHECK (Eq(len,myDet.getLength())); 
    BOOST_CHECK (Eq(angle,myDet.getAngle()));
    BOOST_CHECK (myDet.hasExposureTime() == false);
}

BOOST_AUTO_TEST_CASE( Detection_blackbox_4 )
{
    //same as 1, with tabs in the whitespace
    Detection myDet;
    long int ID = 10001;
    double MJD = 1234.5678;
    double RA = 2.02;
    double dec = 3.03;
    double obscode = 1337;
    std::string objName = "TestingObject1";
    double mag = 4.04;
    double len = 5.05;
    double angle = -6.06;
    std::stringstream ss("");
    ss << ID << "\t" << std::setprecision(12) << MJD << "\t" << RA << "\t" << dec << "\t" <<  mag << "\t"<< obscode
       << "\t" << objName << "\t" << len << "\t" << angle;
    std::string MITIString(ss.str());

    BOOST_CHECK(myDet.isInitialized() == false);
    myDet.fromMITIString(MITIString);
    BOOST_CHECK(myDet.isInitialized() == true);

    BOOST_CHECK (ID == myDet.getID() );
    BOOST_CHECK (Eq(MJD, myDet.getEpochMJD())) ;
    BOOST_CHECK (Eq(RA,myDet.getRA()));
    BOOST_CHECK (Eq(dec,myDet.getDec())) ; 
    BOOST_CHECK (Eq(obscode,myDet.getObscode() ));
    BOOST_CHECK (objName == myDet.getObjName()); 
    BOOST_CHECK (Eq(mag,myDet.getMag()) ); 
    BOOST_CHECK (Eq(len,myDet.getLength())); 
    BOOST_CHECK (Eq(angle,myDet.getAngle()));
    BOOST_CHECK (myDet.hasExposureTime() == false);
}




BOOST_AUTO_TEST_CASE( Detection_blackbox_5 )
{
    //same as above, but with trailing newline
    Detection myDet;
    long int ID = 10001;
    double MJD = 1234.5678;
    double RA = 2.02;
    double dec = 3.03;
    double obscode = 1337;
    std::string objName = "TestingObject1";
    double mag = 4.04;
    double len = 5.05;
    double angle = -6.06;
    std::stringstream ss("");
    ss << ID << " " << std::setprecision(12) << MJD << " " << RA << " " << dec << " " <<  mag << " "<< obscode
       << " " << objName << " " << len << " " << angle << "\n";

    std::string MITIString(ss.str());

    BOOST_CHECK(myDet.isInitialized() == false);
    myDet.fromMITIString(MITIString);
    BOOST_CHECK(myDet.isInitialized() == true);

    BOOST_CHECK (ID == myDet.getID() );

    BOOST_CHECK (Eq(MJD, myDet.getEpochMJD())) ;
    BOOST_CHECK (Eq(RA,myDet.getRA()));
    BOOST_CHECK (Eq(dec,myDet.getDec())) ; 
    BOOST_CHECK (Eq(obscode,myDet.getObscode() ));
    BOOST_CHECK (objName == myDet.getObjName()); 
    BOOST_CHECK (Eq(mag,myDet.getMag()) ); 
    BOOST_CHECK (Eq(len,myDet.getLength())); 
    BOOST_CHECK (Eq(angle,myDet.getAngle()));
    BOOST_CHECK (myDet.hasExposureTime() == false);
}





BOOST_AUTO_TEST_CASE( Detection_blackbox_6 )
{
    //straightforward, but with an etime parameter.
    Detection myDet;
    long int ID = 10001;
    double MJD = 1234.5678;
    double RA = 2.02;
    double dec = 3.03;
    double obscode = 1337;
    std::string objName = "TestingObject1";
    double mag = 4.04;
    double len = 5.05;
    double angle = -6.06;
    double eTime = 7.07;
    std::stringstream ss("");
    ss << ID << " " << std::setprecision(12) << MJD << " " << RA << " " << dec << " " <<  mag << " "<< obscode
       << " " << objName << " " << len << " " << angle << " " << eTime;

    std::string MITIString(ss.str());

    BOOST_CHECK(myDet.isInitialized() == false);
    myDet.fromMITIString(MITIString);
    BOOST_CHECK(myDet.isInitialized() == true);

    BOOST_CHECK (ID == myDet.getID() );

    BOOST_CHECK (Eq(MJD, myDet.getEpochMJD())) ;
    BOOST_CHECK (Eq(RA,myDet.getRA()));
    BOOST_CHECK (Eq(dec,myDet.getDec())) ; 
    BOOST_CHECK (Eq(obscode,myDet.getObscode() ));
    BOOST_CHECK (objName == myDet.getObjName()); 
    BOOST_CHECK (Eq(mag,myDet.getMag()) ); 
    BOOST_CHECK (Eq(len,myDet.getLength())); 
    BOOST_CHECK (Eq(angle,myDet.getAngle()));
    BOOST_CHECK (myDet.hasExposureTime() == true);
    BOOST_CHECK (Eq(myDet.getExposureTime(), eTime));
}




BOOST_AUTO_TEST_CASE( Detection_blackbox_7 )
{
    //uses the new constructor which doesn't use MITI string (no etime)
    long int ID = 10001;
    double MJD = 1234.5678;
    double RA = 2.02;
    double dec = 3.03;
    double obscode = 1337;
    std::string objName = "TestingObject1";
    double mag = 4.04;
    double len = 5.05;
    double angle = -6.06;
    //double eTime = 7.07;

    Detection myDet(ID, MJD, RA, dec, obscode, objName, mag, len, angle);

    BOOST_CHECK(myDet.isInitialized() == true);

    BOOST_CHECK (ID == myDet.getID() );

    BOOST_CHECK (Eq(MJD, myDet.getEpochMJD())) ;
    BOOST_CHECK (Eq(RA,myDet.getRA()));
    BOOST_CHECK (Eq(dec,myDet.getDec())) ; 
    BOOST_CHECK (Eq(obscode,myDet.getObscode() ));
    BOOST_CHECK (objName == myDet.getObjName()); 
    BOOST_CHECK (Eq(mag,myDet.getMag()) ); 
    BOOST_CHECK (Eq(len,myDet.getLength())); 
    BOOST_CHECK (Eq(angle,myDet.getAngle()));
    BOOST_CHECK (myDet.hasExposureTime() == false);
}


BOOST_AUTO_TEST_CASE( Detection_blackbox_8 )
{
    //uses the new constructor which doesn't use MITI string (also, use etime)
    long int ID = 10001;
    double MJD = 1234.5678;
    double RA = 2.02;
    double dec = 3.03;
    double obscode = 1337;
    std::string objName = "TestingObject1";
    double mag = 4.04;
    double len = 5.05;
    double angle = -6.06;
    double eTime = 7.07;

    Detection myDet(ID, MJD, RA, dec, obscode, objName, mag, len, angle, eTime);

    BOOST_CHECK(myDet.isInitialized() == true);

    BOOST_CHECK (ID == myDet.getID() );

    BOOST_CHECK (Eq(MJD, myDet.getEpochMJD())) ;
    BOOST_CHECK (Eq(RA,myDet.getRA()));
    BOOST_CHECK (Eq(dec,myDet.getDec())) ; 
    BOOST_CHECK (Eq(obscode,myDet.getObscode() ));
    BOOST_CHECK (objName == myDet.getObjName()); 
    BOOST_CHECK (Eq(mag,myDet.getMag()) ); 
    BOOST_CHECK (Eq(len,myDet.getLength())); 
    BOOST_CHECK (Eq(angle,myDet.getAngle()));
    BOOST_CHECK (myDet.hasExposureTime() == true);
    BOOST_CHECK (Eq(myDet.getExposureTime(), eTime));
}




/* 
   Detection whitebox tests: Actually, aside from error cases, we have 100%
   coverage through blackbox tests.

   TBD: possibly find a good way to test that we handle bad input sanely?
   for now, I use exit() instead of exceptions, so this isn't really possible.

 */











///////////////////////////////////////////////////////////////////////
//    TRACKLET  TESTS
///////////////////////////////////////////////////////////////////////


// Um, we don't really need any...








///////////////////////////////////////////////////////////////////////
//    POINTANDVALUE TESTS
///////////////////////////////////////////////////////////////////////



BOOST_AUTO_TEST_CASE( PAV_blackbox_1 )
{
    std::vector<double> myPoint;
    myPoint.push_back(1.01);
    myPoint.push_back(2.02);
    myPoint.push_back(-3.03);
    myPoint.push_back(4.04);
    int myValue = 12345;
    KDTree::PointAndValue<int> myPAV;
    myPAV.setPoint(myPoint);
    myPAV.setValue(myValue);

    BOOST_CHECK(myPAV.getValue() == myValue);

    std::vector<double>returnedPoint = myPAV.getPoint();
    BOOST_REQUIRE(returnedPoint.size() == myPoint.size());
    for (unsigned int i = 0; i < myPoint.size(); i++ ) {
        BOOST_CHECK(Eq(myPoint[i], returnedPoint[i]));
    }
}


/* 
   No whitebox tests needed - we have 100% coverage from one silly test...
 */




///////////////////////////////////////////////////////////////////////
//    COMMON OPERATIONS (common.h, common.cc) TESTS
///////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_CASE( Common_fastMedian_blackbox_1 )
{
    std::vector<double> doubles;
    doubles.push_back(5.05);
    doubles.push_back(1.01);
    doubles.push_back(4.04);
    doubles.push_back(3.03);
    doubles.push_back(2.02);
    BOOST_CHECK(Eq(KDTree::Common::fastMedian(doubles),3.03));
}


BOOST_AUTO_TEST_CASE( Common_fastMedian_blackbox_2 )
{
    std::vector<double> doubles;
    doubles.push_back(5.05);
    BOOST_CHECK(Eq(KDTree::Common::fastMedian(doubles),5.05));
}


BOOST_AUTO_TEST_CASE( Common_fastMedian_blackbox_3 )
{
    std::vector<double> doubles;
    doubles.push_back(0.0001);
    for (unsigned int i = 1; i < 2000; i++) 
    {
        doubles.push_back(i * 1.01);
        doubles.push_back(i * -1.01);
    }
    BOOST_CHECK(Eq(KDTree::Common::fastMedian(doubles),0.0001));
}


//fastmedian already has 100% coverage, no need for added whitebox tests

// not testing printDoubleVec - it's only there for debugging and should probably be removed.


BOOST_AUTO_TEST_CASE( Common_areEqual_blackbox_1 )
{
    BOOST_CHECK(KDTree::Common::areEqual(1.000000000001, 1.0) == true);
    BOOST_CHECK(KDTree::Common::areEqual(1.000000001, 1.0) == false);
}

// areEqual has 100% coverage from blackbox

BOOST_AUTO_TEST_CASE( Common_euclideanDistance_blackbox_1 )
{
    std::vector<double> p1, p2;
    p1.push_back(0.0);
    p1.push_back(0.0);
    p1.push_back(0.0);

    p2.push_back(0.0);
    p2.push_back(0.0);
    p2.push_back(10.0);

    BOOST_CHECK(Eq(KDTree::Common::euclideanDistance(p1,p2,3), 10.0));
    
    p1[0] = 0.0;
    p1[0] = 0.0;
    p1[0] = 0.0;
    
    p2[0] = 10.0;
    p2[1] = 0.0;
    p2[2] = 0.0;

    BOOST_CHECK(Eq(KDTree::Common::euclideanDistance(p1,p2,3), 10.0));

    p1[0] = 0.0;
    p1[0] = 0.0;
    p1[0] = 0.0;
    
    p2[0] = 10.0;
    p2[1] = 0.0;
    p2[2] = 0.0;


    BOOST_CHECK(Eq(KDTree::Common::euclideanDistance(p1,p2,3), 10.0));    

}



BOOST_AUTO_TEST_CASE( Common_euclideanDistance_blackbox_2 )
{
    std::vector<double> p1, p2;
    p1.push_back(0.0);
    p1.push_back(0.0);

    p2.push_back(3.0);
    p2.push_back(4.0);

    BOOST_CHECK(Eq(KDTree::Common::euclideanDistance(p1,p2,2), 5.0));    
}


BOOST_AUTO_TEST_CASE( Common_euclideanDistance_blackbox_3 )
{
    std::vector<double> p1, p2;
    p1.push_back(0.0);
    p1.push_back(0.0);

    p2.push_back(-3.0);
    p2.push_back(-4.0);

    BOOST_CHECK(Eq(KDTree::Common::euclideanDistance(p1,p2,2), 5.0));    
}

// euclideanDistance has 100% coverage from blackbox


BOOST_AUTO_TEST_CASE( Common_distance1D_blackbox_1 )
{
    BOOST_CHECK(Eq(KDTree::Common::distance1D(1.0, -5.0, KDTree::Common::EUCLIDEAN), 6.0));    

    BOOST_CHECK(Eq(KDTree::Common::distance1D(1.0, 355.0, KDTree::Common::CIRCULAR_DEGREES), 6.0));    
    BOOST_CHECK(Eq(KDTree::Common::distance1D(1.0, 181.0, KDTree::Common::CIRCULAR_DEGREES), 180.0));    
    BOOST_CHECK(Eq(KDTree::Common::distance1D(0.0, 181.0, KDTree::Common::CIRCULAR_DEGREES), 179.0));    

    BOOST_CHECK(Eq(KDTree::Common::distance1D( 355.0, 1.0, KDTree::Common::CIRCULAR_DEGREES), 6.0));    
    BOOST_CHECK(Eq(KDTree::Common::distance1D(181.0, 1.0, KDTree::Common::CIRCULAR_DEGREES), 180.0));    
    BOOST_CHECK(Eq(KDTree::Common::distance1D(181.0, 0.0, KDTree::Common::CIRCULAR_DEGREES), 179.0));    

    BOOST_CHECK(Eq(KDTree::Common::distance1D(1.0, M_PI, KDTree::Common::CIRCULAR_RADIANS), M_PI - 1.0));
    BOOST_CHECK(Eq(KDTree::Common::distance1D(0.0, M_PI + 1.0, KDTree::Common::CIRCULAR_RADIANS), M_PI - 1.0));
    BOOST_CHECK(Eq(KDTree::Common::distance1D(M_PI, 1.0, KDTree::Common::CIRCULAR_RADIANS), M_PI - 1.0));
    BOOST_CHECK(Eq(KDTree::Common::distance1D(M_PI + 1.0, 0.0, KDTree::Common::CIRCULAR_RADIANS), M_PI - 1.0));

}

// i'm cheating because I know that circularShortestPathLen_deg _rad are called by distance1D so 
// we've really tested those reasonably well already

// these three have 100% coverage from blackbox


BOOST_AUTO_TEST_CASE( Common_regionsOverlap1D_blackbox_1 )
{
    
    BOOST_CHECK((KDTree::Common::regionsOverlap1D(1.0, 2.0, 3.0, 4.0, KDTree::Common::EUCLIDEAN) == false));
    BOOST_CHECK((KDTree::Common::regionsOverlap1D(1.0, 2.0, -1.0, -10, KDTree::Common::EUCLIDEAN) == false));
    BOOST_CHECK((KDTree::Common::regionsOverlap1D(1.0, 2.0, -10.0, -1.0, KDTree::Common::EUCLIDEAN) == false));

    BOOST_CHECK((KDTree::Common::regionsOverlap1D(1.0, 2.0, 1.5, 1.75, KDTree::Common::EUCLIDEAN) == true));
    BOOST_CHECK((KDTree::Common::regionsOverlap1D(1.0, 2.0, -10.0, 1.5, KDTree::Common::EUCLIDEAN) == true));
    BOOST_CHECK((KDTree::Common::regionsOverlap1D(1.0, 2.0, 1.75, 1.5, KDTree::Common::EUCLIDEAN) == true));
    BOOST_CHECK((KDTree::Common::regionsOverlap1D(1.0, 2.0, 1.5, -10.0, KDTree::Common::EUCLIDEAN) == true));
    BOOST_CHECK((KDTree::Common::regionsOverlap1D(1.0, 2.0, -1.0, 10.0, KDTree::Common::EUCLIDEAN) == true));
    BOOST_CHECK((KDTree::Common::regionsOverlap1D(1.0, 2.0, 10.0, -1.0, KDTree::Common::EUCLIDEAN) == true));

    /* recall that this function has bizarre calling conventions (it should
     * probably be rewritten for better readability, but the current version
     * *does* work for our purposes) - they are aLo, aHi, b1, b2, where it is
     * required aLo < aHi, and the range aLo - aHi is assumed NOT to cross the 0
     * (and so may be up to 360 degrees.)

     * HOWEVER, we understand b1-b2 to be the SHORTEST path(s) between b1 and
     * b2.  (so if b1b2 is a semicircle, we always return true - there are two
     * shortest paths) and therefore b1b2 <= 180. (i.e., b1b2 CAN cross the 0,
     * but it *CANNOT* be longer than 180 degrees.)
     */

    BOOST_CHECK((KDTree::Common::regionsOverlap1D(10., 20., 15., 30., KDTree::Common::CIRCULAR_DEGREES) == true));
    BOOST_CHECK((KDTree::Common::regionsOverlap1D(10., 20., 30., 15., KDTree::Common::CIRCULAR_DEGREES) == true));
    BOOST_CHECK((KDTree::Common::regionsOverlap1D(10., 20., 15., 17., KDTree::Common::CIRCULAR_DEGREES) == true));
    BOOST_CHECK((KDTree::Common::regionsOverlap1D(10., 20., 17., 15., KDTree::Common::CIRCULAR_DEGREES) == true));
    BOOST_CHECK((KDTree::Common::regionsOverlap1D(10., 20., 0., 30., KDTree::Common::CIRCULAR_DEGREES) == true));
    BOOST_CHECK((KDTree::Common::regionsOverlap1D(10., 20., 30., 0., KDTree::Common::CIRCULAR_DEGREES) == true));

    BOOST_CHECK((KDTree::Common::regionsOverlap1D(10., 350., 15., 30., KDTree::Common::CIRCULAR_DEGREES) == true));
    BOOST_CHECK((KDTree::Common::regionsOverlap1D(10., 350., 5., 20., KDTree::Common::CIRCULAR_DEGREES) == true));
    BOOST_CHECK((KDTree::Common::regionsOverlap1D(10., 350., 0., 5., KDTree::Common::CIRCULAR_DEGREES) == false));
    BOOST_CHECK((KDTree::Common::regionsOverlap1D(10., 350., -5., 5., KDTree::Common::CIRCULAR_DEGREES) == false));
    BOOST_CHECK((KDTree::Common::regionsOverlap1D(10., 350., 355., 5., KDTree::Common::CIRCULAR_DEGREES) == false));
    BOOST_CHECK((KDTree::Common::regionsOverlap1D(10., 350., 355., 359., KDTree::Common::CIRCULAR_DEGREES) == false));
    BOOST_CHECK((KDTree::Common::regionsOverlap1D(10., 350., -20., 20., KDTree::Common::CIRCULAR_DEGREES) == true));

    BOOST_CHECK((KDTree::Common::regionsOverlap1D(0., M_PI-.5, 1., 1.5, KDTree::Common::CIRCULAR_RADIANS) == true));
    BOOST_CHECK((KDTree::Common::regionsOverlap1D(.5, M_PI-.5, 0., .45, KDTree::Common::CIRCULAR_RADIANS) == false));
    BOOST_CHECK((KDTree::Common::regionsOverlap1D(0., M_PI, 0., .45, KDTree::Common::CIRCULAR_RADIANS) == true));
    BOOST_CHECK((KDTree::Common::regionsOverlap1D(0., M_PI, 0., .45, KDTree::Common::CIRCULAR_RADIANS) == true));
    BOOST_CHECK((KDTree::Common::regionsOverlap1D(M_PI, M_PI + 1, M_PI+.5, .1, KDTree::Common::CIRCULAR_RADIANS) == true));
}

// blackbox coverage here should be 100% except for the error cases, TBD

BOOST_AUTO_TEST_CASE( convertToStandardDegrees_blackbox_1 )
{
    BOOST_CHECK(Eq(KDTree::Common::convertToStandardDegrees(100.), 100.));
    BOOST_CHECK(Eq(KDTree::Common::convertToStandardDegrees(-10.), 350.));
    BOOST_CHECK(Eq(KDTree::Common::convertToStandardDegrees(360.), 0.));
    BOOST_CHECK(Eq(KDTree::Common::convertToStandardDegrees(730.), 10.));
    BOOST_CHECK(Eq(KDTree::Common::convertToStandardDegrees(-360.), 0.));
    BOOST_CHECK(Eq(KDTree::Common::convertToStandardDegrees(-370.), 350.));    
}

//blackbox coverage should be 100% for convertToStandardDegrees

BOOST_AUTO_TEST_CASE( minOfTwo_blackbox_1 )
{
    BOOST_CHECK(Eq(KDTree::Common::minOfTwo(-370., -360), -370.));    
    BOOST_CHECK(Eq(KDTree::Common::minOfTwo(100., -360), -360.));    
    BOOST_CHECK(Eq(KDTree::Common::minOfTwo(100., 100.), 100.));    
    BOOST_CHECK(Eq(KDTree::Common::minOfTwo(0., 0.), 0.));    
}

//blackbox coverage should be 100% for minOfTwo

BOOST_AUTO_TEST_CASE( maxOfTwo_blackbox_1 )
{
    BOOST_CHECK(Eq(KDTree::Common::maxOfTwo(-370., -360), -360.));    
    BOOST_CHECK(Eq(KDTree::Common::maxOfTwo(100., -360), 100.));    
    BOOST_CHECK(Eq(KDTree::Common::maxOfTwo(100., 100.), 100.));    
    BOOST_CHECK(Eq(KDTree::Common::maxOfTwo(0., 0.), 0.));    
}

//blackbox coverage should be 100% for maxOfTwo




BOOST_AUTO_TEST_CASE (arcToRA_1 )
{
     for (double i = 0; i < 90; i+= 10) {
	  double RADist = KDTree::Common::arcToRA(0,i);
	  BOOST_CHECK(Eq(RADist, i));
     }

}


BOOST_AUTO_TEST_CASE( angularDistance_1 )
{
     for (double i = 0; i < 90; i+= 10) {
	  double maxRADist = KDTree::Common::arcToRA(i, 1);
	  double maxAngularDist = KDTree::Common::angularDistanceRADec_deg(0,i,maxRADist,i); 
	  BOOST_CHECK(Eq(maxAngularDist,1.0));
     }
}



BOOST_AUTO_TEST_CASE( angularDistance_2 )
{
     double prior = 190;
     for (double i = 0; i < 90; i+= 10) {
	  double cur = KDTree::Common::angularDistanceRADec_deg(0,i,10,i);
	  BOOST_CHECK(cur < prior);
	  prior = cur;
     }
}

BOOST_AUTO_TEST_CASE( angularDistance_3 )
{
     for (double i = -90; i < 80; i+= 10) {
	  BOOST_CHECK(Eq(10, KDTree::Common::angularDistanceRADec_deg(0,i,0,i+10)));
     }
}




///////////////////////////////////////////////////////////////////////
//    KDTREE TESTS
///////////////////////////////////////////////////////////////////////


/* populate/queryTree with data set 1: a single point, make several queries
 * (some include the point, some don't; some are euclidean, some are in degrees;
 * some queries are from the 'other side' of zero.)
 */

void populateTree_Dataset1(KDTree::KDTree<int> &kdt)
{
    std::vector<KDTree::PointAndValue<int> > myPts;
    KDTree::PointAndValue<int> tmpPAV;

    std::vector<double>tmpPt;
    tmpPt.push_back(10.0);
    tmpPt.push_back(20.0);

    tmpPAV.setPoint(tmpPt);
    tmpPAV.setValue(30);
    myPts.push_back(tmpPAV);

    kdt.buildFromData(myPts, 2, 1);
}



void queryTree_Dataset1(KDTree::KDTree<int> &kdt)
{
    // querypt1, tolerances1, geos1: should reach the point.
    
    std::vector<double>queryPt1;
    queryPt1.push_back(15.0);
    queryPt1.push_back(15.0);
    std::vector<double>tolerances1;
    tolerances1.push_back(5.1);
    tolerances1.push_back(5.1);
    std::vector<KDTree::Common::GeometryType> myGeos1;
    myGeos1.push_back(KDTree::Common::EUCLIDEAN);
    myGeos1.push_back(KDTree::Common::EUCLIDEAN);

    std::vector<KDTree::PointAndValue<int> > queryResults;

    queryResults = kdt.hyperRectangleSearch(queryPt1, tolerances1, myGeos1);
    BOOST_REQUIRE(queryResults.size() == 1);    
    BOOST_CHECK(queryResults[0].getValue() == 30);    

    // queryPt1, tolerances1, geos2 should *also* reach the point.

    std::vector<KDTree::Common::GeometryType> myGeos2;
    myGeos2.push_back(KDTree::Common::CIRCULAR_DEGREES);
    myGeos2.push_back(KDTree::Common::CIRCULAR_DEGREES);

    queryResults = kdt.hyperRectangleSearch(queryPt1, tolerances1, myGeos2);
    BOOST_REQUIRE(queryResults.size() == 1);    
    BOOST_CHECK(queryResults[0].getValue() == 30);    

    //queryPt 1, tolerance2, geos1/2 should *NOT* reach the point.

    std::vector<double>tolerances2;
    tolerances2.push_back(4.9);
    tolerances2.push_back(4.9);
    
    queryResults = kdt.hyperRectangleSearch(queryPt1, tolerances2, myGeos1);
    BOOST_CHECK(queryResults.size() == 0);    
    //geos2, circular degrees
    queryResults = kdt.hyperRectangleSearch(queryPt1, tolerances2, myGeos2);
    BOOST_CHECK(queryResults.size() == 0);    


    //queryPt2: far away.  tolerances3 will reach it, tolerances1/2 will not.
    //specified in euclidean space.
    std::vector<double>queryPt2;
    queryPt2.push_back(-20.0);
    queryPt2.push_back(-10.0);
    
    std::vector<double>tolerances3;
    tolerances3.push_back(30.1);
    tolerances3.push_back(30.1);

    queryResults = kdt.hyperRectangleSearch(queryPt2, tolerances3, myGeos1);
    BOOST_REQUIRE(queryResults.size() == 1);    
    BOOST_CHECK(queryResults[0].getValue() == 30);

    queryResults = kdt.hyperRectangleSearch(queryPt2, tolerances1, myGeos1);
    BOOST_CHECK(queryResults.size() == 0);    
       
    //queryPt3: same, but specified in degrees.
    std::vector<double>queryPt3;
    queryPt3.push_back(340.0);
    queryPt3.push_back(350.0);

    queryResults = kdt.hyperRectangleSearch(queryPt3, tolerances3, myGeos2);
    BOOST_REQUIRE(queryResults.size() == 1);    
    BOOST_CHECK(queryResults[0].getValue() == 30);    

    queryResults = kdt.hyperRectangleSearch(queryPt3, tolerances1, myGeos2);
    BOOST_CHECK(queryResults.size() == 0);    
    
}




BOOST_AUTO_TEST_CASE( KDTree_blackbox_1 )
{
    KDTree::KDTree<int> myKDT;
    KDTree::KDTree<int> myKDT2;

    populateTree_Dataset1(myKDT);
    queryTree_Dataset1(myKDT);

    //test operator= , make sure it works as expected
    myKDT2 = myKDT;
    queryTree_Dataset1(myKDT2);

    //test copy constructor, make sure it works as expected
    KDTree::KDTree<int> myKDT3(myKDT);

    queryTree_Dataset1(myKDT3);
}




/* populate/queryTree with data set 1: 
   this time, 100 pts, basically a grid of all points of the form
   (i,j) where i,j are integers and 0 <= i,j < 10.  each should have a unique ID from 0 to 99.
 */

void populateTree_Dataset2(KDTree::KDTree<int> &kdt)
{
    std::vector<KDTree::PointAndValue<int> > myPts;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            std::vector<double>tmpPt;
            tmpPt.push_back(i);
            tmpPt.push_back(j);            
            KDTree::PointAndValue<int> tmpPAV;
            tmpPAV.setPoint(tmpPt);
            tmpPAV.setValue(i*10+j);
            myPts.push_back(tmpPAV);
        }
    }

    kdt.buildFromData(myPts, 2, 1);
}



void queryTree_Dataset2(KDTree::KDTree<int> &kdt)
{
    // query 1: should get all the points.
    std::vector<double>queryPt1;
    queryPt1.push_back(5.0);
    queryPt1.push_back(5.0);
    std::vector<double>tolerances1;
    tolerances1.push_back(5.1);
    tolerances1.push_back(5.1);
    std::vector<KDTree::Common::GeometryType> myGeos1;
    myGeos1.push_back(KDTree::Common::EUCLIDEAN);
    myGeos1.push_back(KDTree::Common::EUCLIDEAN);

    std::vector<KDTree::PointAndValue<int> > queryResults;
    queryResults = kdt.hyperRectangleSearch(queryPt1, tolerances1, myGeos1);

    //check that we got IDs from from 0 thru 99 inclusive
    BOOST_CHECK(queryResults.size() == 100);
    BOOST_REQUIRE(queryResults.size() > 0);
    std::vector<int>allKeys;
    for (unsigned int i = 0; i < queryResults.size(); i++) 
    {
        allKeys.push_back(queryResults[i].getValue());
    }
    std::sort(allKeys.begin(), allKeys.end());
    for (int i = 0; i < static_cast<int> (allKeys.size()); i++)
    {
	 BOOST_CHECK(allKeys[i] == i);
    }


    // should get a 3x3 grid centered at (5,5)

    std::vector<double>queryPt2;
    queryPt2.push_back(5.0);
    queryPt2.push_back(5.0);
    std::vector<double>tolerances2;
    tolerances2.push_back(1.1);
    tolerances2.push_back(1.1);
    std::vector<KDTree::Common::GeometryType> myGeos2;
    myGeos2.push_back(KDTree::Common::EUCLIDEAN);
    myGeos2.push_back(KDTree::Common::EUCLIDEAN);

    queryResults = kdt.hyperRectangleSearch(queryPt2, tolerances2, myGeos2);

    BOOST_REQUIRE(queryResults.size() == 9);
    allKeys.clear();
    for (unsigned int i = 0; i < queryResults.size(); i++) 
    {
        allKeys.push_back(queryResults[i].getValue());
    }
    std::sort(allKeys.begin(), allKeys.end());

    // we should have 4,4, 4,5, 4,6

    BOOST_CHECK(allKeys[0] == 44);
    BOOST_CHECK(allKeys[1] == 45);
    BOOST_CHECK(allKeys[2] == 46);
    BOOST_CHECK(allKeys[3] == 54);
    BOOST_CHECK(allKeys[4] == 55);
    BOOST_CHECK(allKeys[5] == 56);
    BOOST_CHECK(allKeys[6] == 64);
    BOOST_CHECK(allKeys[7] == 65);
    BOOST_CHECK(allKeys[8] == 66);



    // do a circular degree search, starting at -355, -355 but enclosing all our points
    queryPt2.clear();
    queryPt2.push_back(355.0);
    queryPt2.push_back(355.0);
    tolerances2.clear();
    tolerances2.push_back(20.);
    tolerances2.push_back(20.);
    myGeos2.clear();
    myGeos2.push_back(KDTree::Common::CIRCULAR_DEGREES);
    myGeos2.push_back(KDTree::Common::CIRCULAR_DEGREES);

    queryResults = kdt.hyperRectangleSearch(queryPt2, tolerances2, myGeos2);

    BOOST_REQUIRE(queryResults.size() > 0);
    BOOST_REQUIRE(queryResults.size() == 100);
    allKeys.clear();
    for (unsigned int i = 0; i < queryResults.size(); i++) 
    {
        allKeys.push_back(queryResults[i].getValue());
    }
    std::sort(allKeys.begin(), allKeys.end());
    for (int i = 0; i < static_cast<int>(allKeys.size()); i++)
    {
        BOOST_CHECK(allKeys[i] == i);
    }


}





BOOST_AUTO_TEST_CASE( KDTree_blackbox_2 )
{
    KDTree::KDTree<int> myKDT;
    KDTree::KDTree<int> myKDT2;

    populateTree_Dataset2(myKDT);
    queryTree_Dataset2(myKDT);

    //test operator= , make sure it works as expected
    myKDT2 = myKDT;
    queryTree_Dataset2(myKDT2);

    //test copy constructor, make sure it works as expected
    KDTree::KDTree<int> myKDT3(myKDT);

    queryTree_Dataset2(myKDT3);
}








KDTree::KDTree<int>* makeAndPopulateTree_Dataset3()
{
    std::vector<KDTree::PointAndValue<int> > myPts;

    // 100 copies of the point 10,10

    for (int i = 0; i < 100; i++)
    {
            std::vector<double>tmpPt;
            tmpPt.push_back(10);
            tmpPt.push_back(10);            
            KDTree::PointAndValue<int> tmpPAV;
            tmpPAV.setPoint(tmpPt);
            tmpPAV.setValue(i);
            myPts.push_back(tmpPAV);
    }

    KDTree::KDTree<int>* kdt2 = new KDTree::KDTree<int>(myPts, 2, 1);
    return kdt2;
}




void queryTree_Dataset3(KDTree::KDTree<int> *kdt)
{
    // query 1: should get all the points.
    std::vector<double>queryPt1;
    queryPt1.push_back(10.0);
    queryPt1.push_back(10.0);
    std::vector<double>tolerances1;
    tolerances1.push_back(5.1);
    tolerances1.push_back(5.1);
    std::vector<KDTree::Common::GeometryType> myGeos1;
    myGeos1.push_back(KDTree::Common::EUCLIDEAN);
    myGeos1.push_back(KDTree::Common::EUCLIDEAN);

    std::vector<KDTree::PointAndValue<int> > queryResults;
    queryResults = kdt->hyperRectangleSearch(queryPt1, tolerances1, myGeos1);

    //check that we got IDs from from 0 thru 99 inclusive
    BOOST_CHECK(queryResults.size() == 100);
    BOOST_REQUIRE(queryResults.size() > 0);
    std::vector<int>allKeys;
    for (unsigned int i = 0; i < queryResults.size(); i++) 
    {
        allKeys.push_back(queryResults[i].getValue());
    }
    std::sort(allKeys.begin(), allKeys.end());
    for (int i = 0; i < static_cast<int>(allKeys.size()); i++)
    {
        BOOST_CHECK(allKeys[i] == i);
    }

    // query 1: should get no points.
    queryPt1.clear();
    queryPt1.push_back(100.0);
    queryPt1.push_back(100.0);
    tolerances1.clear();
    tolerances1.push_back(5.1);
    tolerances1.push_back(5.1);

    queryResults = kdt->hyperRectangleSearch(queryPt1, tolerances1, myGeos1);

    BOOST_CHECK(queryResults.size() == 0);


}





BOOST_AUTO_TEST_CASE( KDTree_blackbox_3 )
{
    KDTree::KDTree<int> *myKDT;

    // just to be a bit different (and get more coverage), test a different way
    // of instantiating a KDTree...
    myKDT = makeAndPopulateTree_Dataset3();
    queryTree_Dataset3(myKDT);
    delete myKDT;
}







void insertPoint(std::vector<double> point, int &count, std::vector<KDTree::PointAndValue<int> > &pav) 
{
     KDTree::PointAndValue<int>tmpPav;
     tmpPav.setPoint(point);
     tmpPav.setValue(count);
     count++;
     pav.push_back(tmpPav);
}




BOOST_AUTO_TEST_CASE ( KDTree_john_dailey_bug_unit_test  )
{
/* 
   John Dailey from WISE found this interesting bug in KDTree; if each
   point was distinct, but the median value in each axis was ALSO the
   max value in that axis, then all the values in each axis would get
   indefinitely passed down to the left child; this resulted in
   infinite recursion.
   
   this is the data set he presented:

   >> ra= 1,2,3,3,3,3
   >> dec=5,5,5,5,3,1
   >> V  =4,1,2,4,4,4
   >> A  =8,8,8,8,4,3  */
     
     std::vector<KDTree::PointAndValue <int> > pav;
     int count = 0;
     std::vector<double> tmpPt;
     tmpPt.push_back(1);
     tmpPt.push_back(5);
     tmpPt.push_back(4);
     tmpPt.push_back(8);
     insertPoint(tmpPt, count, pav); 
     tmpPt.clear();

     tmpPt.push_back(2);
     tmpPt.push_back(5);
     tmpPt.push_back(1);
     tmpPt.push_back(8);
     insertPoint(tmpPt, count, pav); 
     tmpPt.clear();

     tmpPt.push_back(3);
     tmpPt.push_back(5);
     tmpPt.push_back(2);
     tmpPt.push_back(8);
     insertPoint(tmpPt, count, pav); 
     tmpPt.clear();

     tmpPt.push_back(3);
     tmpPt.push_back(5);
     tmpPt.push_back(4);
     tmpPt.push_back(8);
     insertPoint(tmpPt, count, pav); 
     tmpPt.clear();

     tmpPt.push_back(3);
     tmpPt.push_back(1);
     tmpPt.push_back(4);
     tmpPt.push_back(3);
     insertPoint(tmpPt, count, pav); 
     tmpPt.clear();

     KDTree::KDTree<int> myTree(pav, 4, 1);
	  
}



BOOST_AUTO_TEST_CASE ( KDTree_RADecRangeSearch_1 )
{
     // test our ability to deal with pole crossers in RADec searches.

     std::vector<KDTree::PointAndValue <int> > pav;
     int count = 0;
     std::vector<double> tmpPt;
     // (0, 89.5)
     tmpPt.push_back(0);
     tmpPt.push_back(89.5);
     insertPoint(tmpPt, count, pav); 
     tmpPt.clear();
     // across the N pole: (180, 89.5)
     tmpPt.push_back(180);
     tmpPt.push_back(89.5);
     insertPoint(tmpPt, count, pav); 
     tmpPt.clear();

     KDTree::KDTree<int> myTree(pav, 2, 1);
     std::vector<double> queryPt;
     queryPt.push_back(0);
     queryPt.push_back(89.5);
     std::vector<double>otherDimsPt;
     std::vector<double>otherDimsTolerances;
     std::vector<KDTree::Common::GeometryType> spaceTypes;
     spaceTypes.push_back(KDTree::Common::RA_DEGREES);
     spaceTypes.push_back(KDTree::Common::DEC_DEGREES);
     std::vector<KDTree::PointAndValue<int> > matches;     
     matches = myTree.RADecRangeSearch(queryPt, 2.0 /* range of 2 deg should return everything */,
				       otherDimsPt, otherDimsTolerances, spaceTypes);
     BOOST_CHECK(matches.size() == 2); 			      
}





BOOST_AUTO_TEST_CASE ( KDTree_RADecRangeSearch_2 )
{
     // test that we're pruning our results correctly using angular great-circle distance, not euclidean

     std::vector<KDTree::PointAndValue <int> > pav;
     int count = 0;
     std::vector<double> tmpPt;
     // (0, 89.5)
     tmpPt.push_back(0);
     tmpPt.push_back(89.5);    
     insertPoint(tmpPt, count, pav); 
     tmpPt.clear();
     //  almost on the pole: (40, 89.8)
     tmpPt.push_back(40);
     tmpPt.push_back(89.8);
     insertPoint(tmpPt, count, pav); 
     tmpPt.clear();

     KDTree::KDTree<int> myTree(pav, 2, 1);
     std::vector<double> queryPt;
     queryPt.push_back(0);
     queryPt.push_back(89.5);
     std::vector<double>otherDimsPt;
     std::vector<double>otherDimsTolerances;
     std::vector<KDTree::Common::GeometryType> spaceTypes;
     spaceTypes.push_back(KDTree::Common::RA_DEGREES);
     spaceTypes.push_back(KDTree::Common::DEC_DEGREES);
     std::vector<KDTree::PointAndValue<int> > matches;     
     matches = myTree.RADecRangeSearch(queryPt, 2.0 /* range of 2 deg should return everything */,
				       otherDimsPt, otherDimsTolerances, spaceTypes);
     BOOST_CHECK(matches.size() == 2); 			      
}



BOOST_AUTO_TEST_CASE ( KDTree_RADecRangeSearch_3 )
{
     // put something right on the north pole, see if things explode

     std::vector<KDTree::PointAndValue <int> > pav;
     int count = 0;
     std::vector<double> tmpPt;
     // (0, 89.5)
     tmpPt.push_back(0);
     tmpPt.push_back(89.5);
     insertPoint(tmpPt, count, pav); 
     tmpPt.clear();
     //  pole: (0, 90)
     tmpPt.push_back(0);
     tmpPt.push_back(90);
     insertPoint(tmpPt, count, pav); 
     tmpPt.clear();

     KDTree::KDTree<int> myTree(pav, 2, 1);
     std::vector<double> queryPt;
     queryPt.push_back(0);
     queryPt.push_back(89.5);
     std::vector<double>otherDimsPt;
     std::vector<double>otherDimsTolerances;
     std::vector<KDTree::Common::GeometryType> spaceTypes;
     spaceTypes.push_back(KDTree::Common::RA_DEGREES);
     spaceTypes.push_back(KDTree::Common::DEC_DEGREES);
     std::vector<KDTree::PointAndValue<int> > matches;     
     matches = myTree.RADecRangeSearch(queryPt, 2.0 /* range of 2 deg should return everything */,
				       otherDimsPt, otherDimsTolerances, spaceTypes);
     BOOST_CHECK(matches.size() == 2); 			      
}




BOOST_AUTO_TEST_CASE ( KDTree_RADecRangeSearch_4 )
{
     // cross the south pole!

     std::vector<KDTree::PointAndValue <int> > pav;
     int count = 0;
     std::vector<double> tmpPt;
     // (0, -89.5)
     tmpPt.push_back(0);
     tmpPt.push_back(KDTree::Common::convertToStandardDegrees(-89.5));
     insertPoint(tmpPt, count, pav); 
     tmpPt.clear();
     //  pole: (180, -89.5)
     tmpPt.push_back(180);
     tmpPt.push_back(KDTree::Common::convertToStandardDegrees(-89.5));
     insertPoint(tmpPt, count, pav); 
     tmpPt.clear();

     KDTree::KDTree<int> myTree(pav, 2, 1);
     std::vector<double> queryPt;
     queryPt.push_back(0);
     queryPt.push_back(-89.5);
     std::vector<double>otherDimsPt;
     std::vector<double>otherDimsTolerances;
     std::vector<KDTree::Common::GeometryType> spaceTypes;
     spaceTypes.push_back(KDTree::Common::RA_DEGREES);
     spaceTypes.push_back(KDTree::Common::DEC_DEGREES);
     std::vector<KDTree::PointAndValue<int> > matches;     
     matches = myTree.RADecRangeSearch(queryPt, 2.0 /* range of 2 deg should return everything */,
				       otherDimsPt, otherDimsTolerances, spaceTypes);
     BOOST_CHECK(matches.size() == 2); 			      
}





BOOST_AUTO_TEST_CASE ( KDTree_RADecRangeSearch_5 )
{
     // check that searching is a circle, not a rectangle

     std::vector<KDTree::PointAndValue <int> > pav;
     int count = 0;
     std::vector<double> tmpPt;
     // (40,35) - some random point
     tmpPt.push_back(40);
     tmpPt.push_back(35);
     insertPoint(tmpPt, count, pav); 
     tmpPt.clear();
     //  a euclidean distance (and angular distance) of ~2.12 away
     //  from origin, where we search: (1.5,1.5)
     tmpPt.push_back(1.5);
     tmpPt.push_back(1.5);
     insertPoint(tmpPt, count, pav); 
     tmpPt.clear();

     KDTree::KDTree<int> myTree(pav, 2, 1);
     std::vector<double> queryPt;
     queryPt.push_back(0);
     queryPt.push_back(0);
     std::vector<double>otherDimsPt;
     std::vector<double>otherDimsTolerances;
     std::vector<KDTree::Common::GeometryType> spaceTypes;
     spaceTypes.push_back(KDTree::Common::RA_DEGREES);
     spaceTypes.push_back(KDTree::Common::DEC_DEGREES);
     std::vector<KDTree::PointAndValue<int> > matches;     
     matches = myTree.RADecRangeSearch(queryPt, 2.0 /* range of 2 deg should return everything */,
				       otherDimsPt, otherDimsTolerances, spaceTypes);
     BOOST_CHECK(matches.size() == 0); 			      
}






BOOST_AUTO_TEST_CASE ( KDTree_RADecRangeSearch_5_1 )
{
     // search in RA, Dec as well as other dimensions - say, RA, Dec, time

     std::vector<KDTree::PointAndValue <int> > pav;
     int count = 0;
     std::vector<double> tmpPt;
     // (0,70) time 100 - some random point
     tmpPt.push_back(0);
     tmpPt.push_back(70);
     tmpPt.push_back(100);
     insertPoint(tmpPt, count, pav); 
     tmpPt.clear();
     // (1,71) at time 101 - just 1.05 away from the original point
     tmpPt.push_back(1);
     tmpPt.push_back(71);
     tmpPt.push_back(101);
     insertPoint(tmpPt, count, pav); 
     tmpPt.clear();

     // (1,71) at time 105
     tmpPt.push_back(1);
     tmpPt.push_back(71);
     tmpPt.push_back(105);
     insertPoint(tmpPt, count, pav); 
     tmpPt.clear();

     KDTree::KDTree<int> myTree(pav, 3, 1);
     std::vector<double> queryPt;
     queryPt.push_back(0);
     queryPt.push_back(70);
     std::vector<double>otherDimsPt;
     otherDimsPt.push_back(100);
     std::vector<double>otherDimsTolerances;
     otherDimsTolerances.push_back(2);
     // the last point should be excluded for being too 'late' in time
     std::vector<KDTree::Common::GeometryType> spaceTypes;
     spaceTypes.push_back(KDTree::Common::RA_DEGREES);
     spaceTypes.push_back(KDTree::Common::DEC_DEGREES);
     spaceTypes.push_back(KDTree::Common::EUCLIDEAN);
     std::vector<KDTree::PointAndValue<int> > matches;     
     matches = myTree.RADecRangeSearch(queryPt, 1.5,
				       otherDimsPt, otherDimsTolerances, spaceTypes);
     BOOST_CHECK(matches.size() == 2); 			      
}


BOOST_AUTO_TEST_CASE ( KDTree_RADecRangeSearch_6 )
{
     // search in RA, Dec as well as other dimensions - say, RA, Dec, time

     std::vector<KDTree::PointAndValue <int> > pav;
     int count = 0;
     std::vector<double> tmpPt;
     // (0,70) time 100 - some random point
     tmpPt.push_back(0);
     tmpPt.push_back(70);
     tmpPt.push_back(100);
     insertPoint(tmpPt, count, pav); 
     tmpPt.clear();
     // (1,71) at time 101 - just 1.05 away from the original point
     tmpPt.push_back(1);
     tmpPt.push_back(71);
     tmpPt.push_back(101);
     insertPoint(tmpPt, count, pav); 
     tmpPt.clear();

     // (0.5,70.5) at time 105
     tmpPt.push_back(.5);
     tmpPt.push_back(70.5);
     tmpPt.push_back(105);
     insertPoint(tmpPt, count, pav); 
     tmpPt.clear();

     KDTree::KDTree<int> myTree(pav, 3, 1);
     std::vector<double> queryPt;
     queryPt.push_back(0);
     queryPt.push_back(70);
     std::vector<double>otherDimsPt;
     otherDimsPt.push_back(100);
     std::vector<double>otherDimsTolerances;
     otherDimsTolerances.push_back(2);
     // the last point should be excluded for being too 'late' in time
     std::vector<KDTree::Common::GeometryType> spaceTypes;
     spaceTypes.push_back(KDTree::Common::RA_DEGREES);
     spaceTypes.push_back(KDTree::Common::DEC_DEGREES);
     spaceTypes.push_back(KDTree::Common::EUCLIDEAN);
     std::vector<KDTree::PointAndValue<int> > matches;     
     matches = myTree.RADecRangeSearch(queryPt, 1.5,
				       otherDimsPt, otherDimsTolerances, spaceTypes);
     BOOST_CHECK(matches.size() == 2); 			      

}








//TBD: whitebox tests, probably after integrating exceptions




///////////////////////////////////////////////////////////////////////
//    RMSLINEFIT TESTS
///////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE( rmsForTracklet_blackbox_1 )
{

    // try four points which have a perfect linear fit; 

    std::vector<Detection> dets;

    Detection tmpDet;
    tmpDet.fromMITIString("0 5330.0 10.0 10.0 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.1 11.0 11.0 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.2 12.0 12.0 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.3 13.0 13.0 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);

    Tracklet t;
    t.indices.insert(0);
    t.indices.insert(1);
    t.indices.insert(2);
    t.indices.insert(3);

    BOOST_CHECK(Eq(rmsLineFit::rmsForTracklet(t, &dets), 0.0));

}


BOOST_AUTO_TEST_CASE( rmsForTracklet_blackbox_2 )
{

    // try four points which deviate very regularly from perfect linear fit - exactly
    // .1 in deg deviation at each point

    std::vector<Detection> dets;

    Detection tmpDet;
    tmpDet.fromMITIString("0 5330.0 10.0 9.9 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.1 11.0 11.1 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.2 12.0 11.9 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.3 13.0 13.1 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);

    Tracklet t;
    t.indices.insert(0);
    t.indices.insert(1);
    t.indices.insert(2);
    t.indices.insert(3);

    double mSqDev = rmsLineFit::rmsForTracklet(t, &dets);
    // each one deviates by .1, so local dist sq is .1*.1.  4 total observations.
    double expected = sqrt((.1*.1)*4) / 4;

    // std::vector<double> RASlopeAndOffset, DecSlopeAndOffset;
    // collapseTracklets::leastSquaresSolveForRADecLinear(&dets, RASlopeAndOffset, 
    //                                                    DecSlopeAndOffset, 5330);

    // std::cout << "RA  Slope, offset: " << RASlopeAndOffset[0] << " , " << RASlopeAndOffset[1] << std::endl;
    // std::cout << "Dec Slope, offset: " << DecSlopeAndOffset[0] << " , " << DecSlopeAndOffset[1] << std::endl;
    // std::cout <<" mSqDev = " << mSqDev << ", expected = "<< expected << std::endl;

    // this is really pretty miserably inaccurate, but that's due to
    // visionWorkbench, it appears.  I'm using an even fuzzier definition of == here...
    
    BOOST_CHECK(fabs(mSqDev - expected) < .01);
}




BOOST_AUTO_TEST_CASE( rmsForTracklet_blackbox_3 )
{

    // no deviation, but RA, Dec both cross the 0 line
    std::vector<Detection> dets;

    Detection tmpDet;
    tmpDet.fromMITIString("0 5330.0 358.0 358.0 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.1 359.0 359.0 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.2 0.0 0.0 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.3 1.0 1.0 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);

    Tracklet t;
    t.indices.insert(0);
    t.indices.insert(1);
    t.indices.insert(2);
    t.indices.insert(3);

    double mSqDev = rmsLineFit::rmsForTracklet(t, &dets);

    BOOST_CHECK(Eq(mSqDev, 0));
}


BOOST_AUTO_TEST_CASE( rmsForTracklet_blackbox_4 )
{

    //same as 3, but going the opposite direction
    std::vector<Detection> dets;

    Detection tmpDet;
    tmpDet.fromMITIString("0 5330.0 1.0 1.0 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.1 0.0 0.0 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.2 359. 359. 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.3 358. 358. 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);

    Tracklet t;
    t.indices.insert(0);
    t.indices.insert(1);
    t.indices.insert(2);
    t.indices.insert(3);

    double mSqDev = rmsLineFit::rmsForTracklet(t, &dets);

    BOOST_CHECK(Eq(mSqDev, 0));
}




BOOST_AUTO_TEST_CASE( getAverageMagnitude_blackbox_1 )
{

    std::vector<Detection> dets;

    Detection tmpDet;
    tmpDet.fromMITIString("0 5330.0 1.0 1.0 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.1 0.0 0.0 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.2 359. 359. 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.3 358. 358. 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);

    Tracklet t;
    t.indices.insert(0);
    t.indices.insert(1);
    t.indices.insert(2);
    t.indices.insert(3);
    
    BOOST_CHECK(Eq(rmsLineFit::getAverageMagnitude(t, &dets), 20.0));
}


BOOST_AUTO_TEST_CASE( getAverageMagnitude_blackbox_2 )
{

    std::vector<Detection> dets;

    Detection tmpDet;
    tmpDet.fromMITIString("0 5330.0 1.0 1.0 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.1 0.0 0.0 22.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.2 359. 359. 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.3 358. 358. 22.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);

    Tracklet t;
    t.indices.insert(0);
    t.indices.insert(1);
    t.indices.insert(2);
    t.indices.insert(3);
    
    BOOST_CHECK(Eq(rmsLineFit::getAverageMagnitude(t, &dets), 21.0));
}


// TBD: uncomment this and use real exceptions. (It's commented out because it causes an exit()
// BOOST_AUTO_TEST_CASE( getAverageMagnitude_blackbox_3 )
// {
//     //try to cause trouble with empty tracklet

//     std::vector<Detection> dets;

//     Detection tmpDet;
//     tmpDet.fromMITIString("0 5330.0 1.0 1.0 20.0 1337 dummy 0.0 0.0"); 
//     dets.push_back(tmpDet);
//     tmpDet.fromMITIString("0 5330.1 0.0 0.0 20.0 1337 dummy 0.0 0.0"); 
//     dets.push_back(tmpDet);
//     tmpDet.fromMITIString("0 5330.2 359. 359. 20.0 1337 dummy 0.0 0.0"); 
//     dets.push_back(tmpDet);
//     tmpDet.fromMITIString("0 5330.3 358. 358. 20.0 1337 dummy 0.0 0.0"); 
//     dets.push_back(tmpDet);

//     Tracklet t;
    
//     BOOST_CHECK(Eq(rmsLineFit::getAverageMagnitude(t, &dets), 20.0));
// }




BOOST_AUTO_TEST_CASE( filterByLineFitAddToOutputVector_blackbox_1 )
{

    std::vector<Detection> dets;

    Detection tmpDet;
    // 4 matching detections
    tmpDet.fromMITIString("0 5330.0 1.0 1.0 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.1 0.0 0.0 22.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.2 359. 359. 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.3 358. 358. 22.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);

    // 4 unrelated detections
    tmpDet.fromMITIString("0 5330.0 1.0 1.0 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.1 10.0 0.0 22.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.2 359. 349. 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.3 18. 358. 22.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);

    std::vector<Tracklet> allTracklets;
    Tracklet t1, t2;
    t1.indices.insert(0);
    t1.indices.insert(1);
    t1.indices.insert(2);
    t1.indices.insert(3);

    t2.indices.insert(4);
    t2.indices.insert(5);
    t2.indices.insert(6);
    t2.indices.insert(7);

    allTracklets.push_back(t1);
    allTracklets.push_back(t2);
    
    std::vector<Tracklet> results;

    rmsLineFit::filterByLineFitAddToOutputVector(&allTracklets, &dets, 0., .1, results);
    
    BOOST_REQUIRE(results.size() == 1);
    
    BOOST_CHECK(results[0].indices == t1.indices);
}




BOOST_AUTO_TEST_CASE( filterByLineFitAddToOutputVector_blackbox_2 )
{
    //try to cause an error by sending in no tracklets

    std::vector<Detection> dets;

    Detection tmpDet;
    // 4 matching detections
    tmpDet.fromMITIString("0 5330.0 1.0 1.0 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.1 0.0 0.0 22.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.2 359. 359. 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.3 358. 358. 22.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);

    // 4 unrelated detections
    tmpDet.fromMITIString("0 5330.0 1.0 1.0 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.1 10.0 0.0 22.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.2 359. 349. 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.3 18. 358. 22.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);

    Tracklet t1, t2;
    
    std::vector<Tracklet> results;
    std::vector<Tracklet> allTracklets;

    rmsLineFit::filterByLineFitAddToOutputVector(&allTracklets, &dets, 0., .1, results);
    
    BOOST_REQUIRE(results.size() == 0);
    
}


// TBD: need to uncomment this after all Exceptions are in place.
// BOOST_AUTO_TEST_CASE( filterByLineFitAddToOutputVector_blackbox_3 )
// {
//     //try to cause an error by sending in *empty* tracklets...

//     std::vector<Detection> dets;

//     Detection tmpDet;
//     // 4 matching detections
//     tmpDet.fromMITIString("0 5330.0 1.0 1.0 20.0 1337 dummy 0.0 0.0"); 
//     dets.push_back(tmpDet);
//     tmpDet.fromMITIString("0 5330.1 0.0 0.0 22.0 1337 dummy 0.0 0.0"); 
//     dets.push_back(tmpDet);
//     tmpDet.fromMITIString("0 5330.2 359. 359. 20.0 1337 dummy 0.0 0.0"); 
//     dets.push_back(tmpDet);
//     tmpDet.fromMITIString("0 5330.3 358. 358. 22.0 1337 dummy 0.0 0.0"); 
//     dets.push_back(tmpDet);

//     // 4 unrelated detections
//     tmpDet.fromMITIString("0 5330.0 1.0 1.0 20.0 1337 dummy 0.0 0.0"); 
//     dets.push_back(tmpDet);
//     tmpDet.fromMITIString("0 5330.1 10.0 0.0 22.0 1337 dummy 0.0 0.0"); 
//     dets.push_back(tmpDet);
//     tmpDet.fromMITIString("0 5330.2 359. 349. 20.0 1337 dummy 0.0 0.0"); 
//     dets.push_back(tmpDet);
//     tmpDet.fromMITIString("0 5330.3 18. 358. 22.0 1337 dummy 0.0 0.0"); 
//     dets.push_back(tmpDet);

//     Tracklet t1, t2;
    
//     std::vector<Tracklet> results;
//     std::vector<Tracklet> allTracklets;
//     allTracklets.push_back(t1);
//     allTracklets.push_back(t2);

//     rmsLineFit::filterByLineFitAddToOutputVector(&allTracklets, &dets, 0., .1, results);
    
//     // not even sure what expected behavior is here... BOOST_REQUIRE(results.size() == 2);
    
// }



BOOST_AUTO_TEST_CASE( filterByLineFitAddToOutputVector_blackbox_4 )
{
    // test with one 'perfect' tracklet, one with a way-off detection.
    std::vector<Detection> dets;

    Detection tmpDet;
    // 4 matching detections
    tmpDet.fromMITIString("0 5330.0 1.0 1.0 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.1 0.0 0.0 22.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.2 359. 359. 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.3 358. 358. 22.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);

    // 4 unrelated detections
    tmpDet.fromMITIString("0 5330.0 1.0 1.0 20.0 1337 dummy2 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.1 0.0 0.0 22.0 1337 dummy2 0.0 0.0"); 
    dets.push_back(tmpDet);
    // this one is way out there
    tmpDet.fromMITIString("0 5330.2 359. 349. 20.0 1337 dummy2 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.3 358. 358. 22.0 1337 dummy2 0.0 0.0"); 
    dets.push_back(tmpDet);
    

    std::vector<Tracklet> allTracklets;
    Tracklet t1, t2;
    t1.indices.insert(0);
    t1.indices.insert(1);
    t1.indices.insert(2);
    t1.indices.insert(3);

    t2.indices.insert(4);
    t2.indices.insert(5);
    t2.indices.insert(6);
    t2.indices.insert(7);

    allTracklets.push_back(t1);
    allTracklets.push_back(t2);

    std::vector<Tracklet> resultTracklets;
    rmsLineFit::filterByLineFitAddToOutputVector(&allTracklets, &dets, 0.0, .1, resultTracklets);
    
    BOOST_REQUIRE(resultTracklets.size() == 1);
    BOOST_CHECK(resultTracklets[0].indices == t1.indices);
}



BOOST_AUTO_TEST_CASE( filterByLineFitAddToOutputVector_blackbox_5 )
{
    // test with one 'perfect' tracklet, one with all detections all a little off.
    std::vector<Detection> dets;

    Detection tmpDet;
    // 4 matching detections
    tmpDet.fromMITIString("0 5330.0 1.0 1.0 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.1 0.0 0.0 22.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.2 359. 359. 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.3 358. 358. 22.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);

    // 4 unrelated detections
    tmpDet.fromMITIString("0 5330.0 1.0 .8 20.0 1337 dummy2 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.1 0.0 .2 22.0 1337 dummy2 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.2 359. 358.8 20.0 1337 dummy2 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.3 358. 358.2 22.0 1337 dummy2 0.0 0.0"); 
    dets.push_back(tmpDet);
    

    std::vector<Tracklet> allTracklets;
    Tracklet t1, t2;
    t1.indices.insert(0);
    t1.indices.insert(1);
    t1.indices.insert(2);
    t1.indices.insert(3);

    t2.indices.insert(4);
    t2.indices.insert(5);
    t2.indices.insert(6);
    t2.indices.insert(7);

    allTracklets.push_back(t1);
    allTracklets.push_back(t2);

    std::vector<Tracklet> resultTracklets;
    rmsLineFit::filterByLineFitAddToOutputVector(&allTracklets, &dets, 0.0, .05, resultTracklets);
    
    BOOST_REQUIRE(resultTracklets.size() == 1);
    BOOST_CHECK(resultTracklets[0].indices == t1.indices);
}





BOOST_AUTO_TEST_CASE( purifyTracklet_blackbox_1 )
{
    // test with one 'perfect' tracklet, one with a barely-off detection.
    std::vector<Detection> dets;

    Detection tmpDet;
    // 4 matching detections
    tmpDet.fromMITIString("0 5330.0 1.0 1.0 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.1 0.0 0.0 22.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.2 359. 359. 20.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.3 358. 358. 22.0 1337 dummy 0.0 0.0"); 
    dets.push_back(tmpDet);

    // 4 unrelated detections
    tmpDet.fromMITIString("0 5330.0 1.0 1.0 20.0 1337 dummy2 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.1 0.0 0.0 22.0 1337 dummy2 0.0 0.0"); 
    dets.push_back(tmpDet);
    // this one is a little off
    tmpDet.fromMITIString("0 5330.2 359. 359.2 20.0 1337 dummy2 0.0 0.0"); 
    dets.push_back(tmpDet);
    tmpDet.fromMITIString("0 5330.3 358. 358. 22.0 1337 dummy2 0.0 0.0"); 
    dets.push_back(tmpDet);
    

    std::vector<Tracklet> allTracklets;
    Tracklet t1, t2, t1Pure, t2Pure;
    
    t1.indices.insert(0);
    t1.indices.insert(1);
    t1.indices.insert(2);
    t1.indices.insert(3);

    t2.indices.insert(4);
    t2.indices.insert(5);
    t2.indices.insert(6);
    t2.indices.insert(7);

    allTracklets.push_back(t1);
    allTracklets.push_back(t2);

    std::vector<Tracklet> resultTracklets;
    rmsLineFit::TrackletPurifier myPure;
    t1Pure = myPure.purifyTracklet(&t1, &dets, 0.0, .1);
    t2Pure = myPure.purifyTracklet(&t2, &dets, 0.0, .1);
    
    BOOST_CHECK(t1Pure.indices == t1.indices);
    std::set<unsigned int> t2Expected;

    t2Expected.insert(4);
    t2Expected.insert(5);
    t2Expected.insert(7);
    
    BOOST_CHECK(t2Pure.indices == t2Expected);

}



// TBD: proper tests of rmsLineFitMain and rmsPurifyMain.
// this will require some data files to use as input...


///////////////////////////////////////////////////////////////////////
//    REMOVESUBSETS TESTS
///////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_CASE( guessBoolFromStringOrGiveErr_blackbox_1 )
{

    BOOST_CHECK(KDTree::Common::guessBoolFromStringOrGiveErr("true", "some error string") == true);
    BOOST_CHECK(KDTree::Common::guessBoolFromStringOrGiveErr("false", "some error string") == false);
    BOOST_CHECK(KDTree::Common::guessBoolFromStringOrGiveErr("TRUE", "some error string") == true);
    BOOST_CHECK(KDTree::Common::guessBoolFromStringOrGiveErr("FALSE", "some error string") == false);
    BOOST_CHECK(KDTree::Common::guessBoolFromStringOrGiveErr("True", "some error string") == true);
    BOOST_CHECK(KDTree::Common::guessBoolFromStringOrGiveErr("False", "some error string") == false);
}


BOOST_AUTO_TEST_CASE( removeSubsetsPopulateOutputVector_blackbox_1 )
{
    std::vector<Tracklet> pairsVec;
    Tracklet lastOne;
    for (int i = 1; i < 200; i++)
    {
        Tracklet tmp;
        for (int j = 0; j < i; j++)
        {
            tmp.indices.insert(j);            
        }
        pairsVec.push_back(tmp);
        if (i == 199) {
            lastOne = tmp;
        }
    }
    std::vector<Tracklet> results;
    removeSubsets::SubsetRemover mySR;
    mySR.removeSubsetsPopulateOutputVector(&pairsVec, results);
    BOOST_REQUIRE(results.size() == 1);
    BOOST_CHECK(results[0].indices == lastOne.indices);
}


BOOST_AUTO_TEST_CASE( removeSubsetsPopulateOutputVector_blackbox_2 )
{
    std::vector<Tracklet> pairsVec;
    Tracklet lastOne;
    for (int i = 1; i < 200; i++)
    {
        Tracklet tmp;
        for (int j = 0; j < i; j++)
        {
            tmp.indices.insert(j);            
        }
        pairsVec.push_back(tmp);
        if (i == 199) {
            lastOne = tmp;
        }
    }
    // and add one that's totally different
    Tracklet t2;
    t2.indices.insert(500);
    t2.indices.insert(505);
    pairsVec.push_back(t2);
    std::vector<Tracklet> results;
    removeSubsets::SubsetRemover mySR;
    mySR.removeSubsetsPopulateOutputVector(&pairsVec, results);
    BOOST_REQUIRE(results.size() == 2);
    BOOST_CHECK(((results[0].indices == lastOne.indices) && (results[1].indices == t2.indices))
                ||
                (results[1].indices == lastOne.indices) && (results[0].indices == t2.indices));

}



BOOST_AUTO_TEST_CASE( putLongestOnlyInOutputVector_blackbox_1 )
{
    // send in the following tracklets:
    // 0 1 2 
    // 0 4

    // should get the same stuff out - 0 1 2 is longest for 0, 1, 2 and 0 4 is longest for 4.

    std::vector<Tracklet> pairsVec;
    Tracklet tmp;
    tmp.indices.insert(0);
    tmp.indices.insert(1);
    tmp.indices.insert(2);
    pairsVec.push_back(tmp);

    tmp.indices.clear();
    tmp.indices.insert(0);
    tmp.indices.insert(4);
    pairsVec.push_back(tmp);
    
    std::vector<Tracklet> out;
    removeSubsets::putLongestPerDetInOutputVector(&pairsVec, out);
    BOOST_CHECK(out.size() == 2);
}



BOOST_AUTO_TEST_CASE( putLongestOnlyInOutputVector_blackbox_2 )
{
    // send in the following tracklets:
    // 0 1 2 
    // 0 4
    // 4 5 6

    // should get just 0 1 2 and 4 5 6.  0 4 is longest for neither 0 nor 4.

    std::vector<Tracklet> pairsVec;
    Tracklet tmp;
    tmp.indices.insert(0);
    tmp.indices.insert(1);
    tmp.indices.insert(2);
    pairsVec.push_back(tmp);

    tmp.indices.clear();
    tmp.indices.insert(0);
    tmp.indices.insert(4);
    pairsVec.push_back(tmp);

    tmp.indices.clear();
    tmp.indices.insert(4);
    tmp.indices.insert(5);
    tmp.indices.insert(6);
    pairsVec.push_back(tmp);
    
    std::vector<Tracklet> out;
    removeSubsets::putLongestPerDetInOutputVector(&pairsVec, out);
    BOOST_CHECK(out.size() == 2);
        
}



// TBD: removeSubsetsMain.  This will also require some external files.  Probably 
// better accomplished with some shell scripts...






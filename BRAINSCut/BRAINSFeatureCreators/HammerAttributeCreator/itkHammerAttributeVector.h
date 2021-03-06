/*=========================================================================

Program:   Hierarchical Attribute Matching Mechanism for Elastic Registration
Module:    $RCSfile: itkHammerAttributeVector.h,v $
Language:  C++
Date:      $Date: 2009/01/13 20:19:20 $
Version:   $Revision: 1.4 $

Copyright (c)

This program is developed under NIH NCBC collaboration grant
R01 EB006733, "Development and Dissemination of Robust Brain MRI
Measurement Tools".

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkHammerAttributeVector_h
#define __itkHammerAttributeVector_h

#include "itkFixedArray.h"

namespace itk
{
/** \class HammerAttributeVector
  * \brief Abstract base class for attribute vector used by Hammer
  *
  */
template <class TValueType, unsigned int VLength = 3>
class ITK_EXPORT HammerAttributeVector :
  public FixedArray<TValueType, VLength>
{
public:
  /** Standard class typedefs. */
  typedef HammerAttributeVector           Self;
  typedef FixedArray<TValueType, VLength> Superclass;
  typedef SmartPointer<Self>              Pointer;
  typedef SmartPointer<const Self>        ConstPointer;
  typedef FixedArray<TValueType, VLength> VectorType;

  /** Length constant */
  itkStaticConstMacro(Length, unsigned int, VLength);

  /** Dimension constant */
  itkStaticConstMacro(Dimension, unsigned int, VLength);

  /** The element type stored at each location in the FixedArray. */
  typedef TValueType ValueType;

  /** A type representing the C-array version of this FixedArray. */
  typedef ValueType CArray[VLength];

  /** An iterator through the array. */
  typedef ValueType *Iterator;

  /** A const iterator through the array. */
  typedef const ValueType *ConstIterator;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(HammerAttributeVector, FixedArray);

  /** define interface for computing similarity/difference between two
    * attribute vectors */
  virtual double ComputeSimilarity(const VectorType & vec2) const
  {
    double diff = 0;
    double mag1 = 0;
    double mag2 = 0;
    for( unsigned int k = 0; k < Length; k++ )
      {
      const double a = static_cast<double>( this->operator[](k) );
      const double b = static_cast<double>( vec2[k] );
      diff += ( a - b ) * ( a - b );
      mag1 += a * a;
      mag2 += b * b;
      }
    diff /= vcl_sqrt(mag1 * mag2);
    return vcl_asin(diff);
  }

  virtual double ComputeDifference(const VectorType & vec2) const
  {
    double diff = 0;
    for( unsigned int k = 0; k < Length; k++ )
      {
      const double a = static_cast<double>( this->operator[](k) );
      const double b = static_cast<double>( vec2[k] );
      diff += ( a - b ) * ( a - b );
      }
    return vcl_sqrt(diff);
  }

protected:
  HammerAttributeVector();
  // virtual ~HammerAttributeVector();
  void PrintSelf(std::ostream & os, Indent indent) const;

private:
  HammerAttributeVector(const Self &);   // purposely not implemented
};

template <typename TValueType, unsigned int VLength>
HammerAttributeVector<TValueType, VLength>
::HammerAttributeVector()
{
}

template <typename TValueType, unsigned int VLength>
void HammerAttributeVector<TValueType, VLength>
::PrintSelf(std::ostream & os, Indent indent) const
{
}

}   // end namespace itk

#endif

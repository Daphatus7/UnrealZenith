// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicUserWidget.h"
#include "Rendering/DrawElements.h"

int32 UDynamicUserWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	// Define the triangle vertices
	FVector2D Vertex1(AllottedGeometry.GetLocalSize().X / 2, 0);
	FVector2D Vertex2(0, AllottedGeometry.GetLocalSize().Y);
	FVector2D Vertex3(AllottedGeometry.GetLocalSize().X, AllottedGeometry.GetLocalSize().Y);

	// Create an array of vertices
	TArray<FVector2D> TriangleVertices;
	TriangleVertices.Add(Vertex1);
	TriangleVertices.Add(Vertex2);
	TriangleVertices.Add(Vertex3);

	// Define the paint geometry
	FSlateDrawElement::MakeLines(
		OutDrawElements,
		LayerId,
		AllottedGeometry.ToPaintGeometry(),
		TriangleVertices,
		ESlateDrawEffect::None,
		FLinearColor::White,
		true, // bAntialias
		2.0f // Thickness
	);

	return LayerId;
}

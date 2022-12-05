from rest_framework import generics
from rest_framework.response import Response
from .serializer import MetricsSerializer

class MetricsView(generics.GenericAPIView):
    serializer_class = MetricsSerializer

    def post(self, request, *args, **kwargs):
        serializer = self.serializer_class(data = request.data)
        if (serializer.is_valid()):
            serializer.save()
            return Response(data = "OK", status = 201)
        return Response(data = "ERROR", status = 400)
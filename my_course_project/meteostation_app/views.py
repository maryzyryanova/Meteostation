from urllib import request
from rest_framework import generics
from rest_framework.response import Response
from .serializer import MetricsSerializer
from django.views import View
from .models import Metrics
from django.shortcuts import render

class MetricsView(generics.GenericAPIView):
    serializer_class = MetricsSerializer

    def post(self, request, *args, **kwargs):
        serializer = self.serializer_class(data = request.data)
        if (serializer.is_valid()):
            serializer.save()
            return Response(data = "OK", status = 201)
        return Response(data = "ERROR", status = 400)

class WeatherForecastView(View):
    template_name = "html/weather_forecast.html"

    def get(self, request):
        metrics = Metrics.objects.all().order_by("-datetime")[0]
        plot_data = Metrics.objects.all().order_by("datetime")[:6]
        return render(
            request,
            self.template_name,
            {
                "metrics": metrics,
                "plot_data": plot_data,
            },
        )

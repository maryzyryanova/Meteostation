from django.urls import path
from .views import MetricsView, WeatherForecastView

urlpatterns = [
    path('send/', MetricsView.as_view()),
    path('', WeatherForecastView.as_view()),
]
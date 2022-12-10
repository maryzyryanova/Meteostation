from django.urls import path
from .views import MetricsView, WeatherForecastView

urlpatterns = [
    path('', WeatherForecastView.as_view()),
    path('send/', MetricsView.as_view()),
]
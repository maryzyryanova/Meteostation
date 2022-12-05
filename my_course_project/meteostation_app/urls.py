from django.urls import path
from .views import MetricsView

urlpatterns = [
    path('send/', MetricsView.as_view()),
]
const API_BASE = 'http://localhost:8080';

document.addEventListener("DOMContentLoaded", () => {
  const loginForm = document.getElementById("loginForm");
  const registerForm = document.getElementById("registerForm");

  if (loginForm) {
    loginForm.addEventListener("submit", async (e) => {
      e.preventDefault();
      const name = document.getElementById("loginName").value;
      const password = document.getElementById("loginPassword").value;

      try {
        const res = await fetch(`${API_BASE}/login`, {
          method: "POST",
          headers: { "Content-Type": "application/json" },
          body: JSON.stringify({ name, password })
        });

        const data = await res.json();
        console.log(data);
        if (data.status === "success") {
          localStorage.setItem("userId", data.userId);
          alert("Login successful!");
        } else {
          alert(data.message || "Login failed");
        }
      } catch (err) {
        console.error(err);
        alert("Error contacting server.");
      }
    });
  }

  if (registerForm) {
    registerForm.addEventListener("submit", async (e) => {
      e.preventDefault();
      const name = document.getElementById("registerName").value;
      const password = document.getElementById("registerPassword").value;
      const initialBalance = parseFloat(document.getElementById("initialBalance").value);

      try {
        const res = await fetch(`${API_BASE}/register`, {
          method: "POST",
          headers: { "Content-Type": "application/json" },
          body: JSON.stringify({ name, password, initialBalance })
        });

        const data = await res.json();
        console.log(data);
        alert(data.message || (data.status === "success" ? "Registered!" : "Error registering"));
      } catch (err) {
        console.error(err);
        alert("Error contacting server.");
      }
    });
  }
});

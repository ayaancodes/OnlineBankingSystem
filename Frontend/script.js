const API_BASE = 'http://localhost:8080';

document.addEventListener("DOMContentLoaded", () => {
  const loginForm = document.getElementById("loginForm");
  const registerForm = document.getElementById("registerForm");
  const depositForm = document.getElementById("depositForm");
  const withdrawForm = document.getElementById("withdrawForm");
  const transferForm = document.getElementById("transferForm");
  const balanceDisplay = document.getElementById("balance");

  // LOGIN
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
        if (data.status === "success") {
          localStorage.setItem("userId", data.userId);
          alert("Login successful!");
          window.location.href = "dashboard.html";
        } else {
          alert(data.message || "Login failed");
        }
      } catch (err) {
        console.error(err);
        alert("Error contacting server.");
      }
    });
  }

  // REGISTER
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
        alert(data.message || (data.status === "success" ? "Registered!" : "Error registering"));
      } catch (err) {
        console.error(err);
        alert("Error contacting server.");
      }
    });
  }

  // DEPOSIT
  if (depositForm) {
    depositForm.addEventListener("submit", async (e) => {
      e.preventDefault();
      const userId = parseInt(localStorage.getItem("userId"));
      const amount = parseFloat(document.getElementById("depositAmount").value);

      try {
        const res = await fetch(`${API_BASE}/deposit`, {
          method: "POST",
          headers: { "Content-Type": "application/json" },
          body: JSON.stringify({ userId, amount })
        });

        const data = await res.json();
        alert(data.message || "Deposit failed.");
      } catch (err) {
        console.error(err);
        alert("Error contacting server.");
      }
    });
  }

  // WITHDRAW
  if (withdrawForm) {
    withdrawForm.addEventListener("submit", async (e) => {
      e.preventDefault();
      const userId = parseInt(localStorage.getItem("userId"));
      const amount = parseFloat(document.getElementById("withdrawAmount").value);

      try {
        const res = await fetch(`${API_BASE}/withdraw`, {
          method: "POST",
          headers: { "Content-Type": "application/json" },
          body: JSON.stringify({ userId, amount })
        });

        const data = await res.json();
        alert(data.message || "Withdrawal failed.");
      } catch (err) {
        console.error(err);
        alert("Error contacting server.");
      }
    });
  }

  // TRANSFER
  if (transferForm) {
    transferForm.addEventListener("submit", async (e) => {
      e.preventDefault();
      const senderId = parseInt(localStorage.getItem("userId"));
      const receiverId = parseInt(document.getElementById("receiverId").value);
      const amount = parseFloat(document.getElementById("transferAmount").value);

      try {
        const res = await fetch(`${API_BASE}/transfer`, {
          method: "POST",
          headers: { "Content-Type": "application/json" },
          body: JSON.stringify({ senderId, receiverId, amount })
        });

        const data = await res.json();
        alert(data.message || "Transfer failed.");
      } catch (err) {
        console.error(err);
        alert("Error contacting server.");
      }
    });
  }

  // DISPLAY BALANCE ON DASHBOARD
  if (balanceDisplay) {
    const userId = localStorage.getItem("userId");
    if (!userId) {
      alert("You must be logged in!");
      window.location.href = "index.html";
      return;
    }

    fetch(`${API_BASE}/balance?userId=${userId}`)
      .then(res => res.json())
      .then(data => {
        balanceDisplay.textContent = `Current Balance: $${data.balance.toFixed(2)}`;
      })
      .catch(err => {
        console.error(err);
        balanceDisplay.textContent = "Failed to load balance.";
      });
  }
});
